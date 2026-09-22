# Aesir Interactive — Programming Task

Technical test for Senior/Lead Game Programmer position. First-person wave-defense: non-aggressive enemies spawn in waves and walk toward a fixed destination point; the player must stop them from arriving before the match timer runs out.

## Requirements

- **Unreal Engine 5.8.2**
- **Visual Studio 2022** (17.x, the toolchain UE 5.8 targets) or **Rider for Unreal Engine**
- **Windows SDK version 10.0.22621.0**

## Project Structure

### `Source/JuanEscuderoTask/`
Single runtime module, split into `Public/`/`Private/`:

- **Core/**
- **Gameplay/**
- **AI/**
- **UI/**

### `Config/`
Standard `DefaultEngine.ini` / `DefaultGame.ini` / `DefaultInput.ini`. `DefaultEngine.ini` also defines four custom collision profiles/trace channels (`Interactable`, `Interactor`, `Weapon`, `Enemy`) used by the interaction and enemy-collision code.

## Architecture

**Composition over inheritance.** Gameplay is built from focused `UActorComponent`s (`HealthComponent`, `InteractionComponent`, `WeaponComponent`) attached to plain actors, instead of a deep per-actor-type class hierarchy. Actors keep a thin C++ base only to host the glue code that reacts to their own components' events (e.g. `AEnemy` binds `HealthComponent::OnHealthDepleted` to fire its own `OnDied`).

Communication follows **call-down/signal-up**: actors know their own components and call them directly (call-down), while components stay agnostic and independent, communicating upward via events/delegates (signal-up) rather than referencing their owning actor's concrete type.

**Communication rules**, applied consistently across the codebase:

| Relationship | Mechanism | Example |
|---|---|---|
| Actor → its own component | Direct call | `AWeapon::Fire()` called by `UWeaponComponent::Use()` |
| Component → its owning actor | Delegate (dynamic multicast) | `HealthComponent::OnHealthDepleted` → `AEnemy::HandleHealthDepleted` |
| GameMode → GameState | Direct call (ownership) | `DefenseGameMode` writes match state directly |
| Multiple concrete types, same contract | Interface (`UInterface`) | `IInteractable`, implemented by `APickup` and checked generically by `UInteractionComponent` |

**C++ vs Blueprint.** Rules, state, and orchestration are C++: game mode/state, all components, the interface, delegates, the State Tree task, the view model. Blueprints hold presentation and tuning: mesh/animation per actor (e.g. `BP_Banshee` extends `AEnemy`), `EditAnywhere` numeric tuning (`MatchDuration`, `MaxBreachesAllowed`, spawn intervals, weapon stats), the State Tree graph itself (`ST_Banshee` — composed visually, but its custom task runs C++ code), and UMG widget layout/bindings (`WBP_HUD`, `WBP_MainMenu`).

## Unreal (post-5.0) Features

- **Enhanced Input** — `InputDataConfig` data asset + `PlayerCharacter`/`DefensePlayerController` bind Input Actions and add the Input Mapping Context via the Enhanced Input subsystem. Standard replacement for the legacy input system since 5.1.
- **State Tree** (`GameplayStateTree` plugin) — drives enemy AI. `EnemyAIController` owns a `StateTreeAIComponent` started on possess; the custom `FFindDestinationTask` reads the match's destination actor from `DefenseGameState` for the tree to path toward. Chosen because it's the paradigm Epic is pushing Unreal's AI toward.
- **MVVM (`ModelViewViewModel`)** — `HUDViewModel` (`UMVVMViewModelBase`) exposes `FieldNotify` properties (time remaining, breach count, ammo, interaction prompt, match result) bound declaratively in `WBP_HUD`; `DefensePlayerController::CreateHUD` wires it via `UMVVMSubsystem`. Scoped to the gameplay HUD only — the main menu has no dynamic state, so it uses a plain `OnClicked` event instead.

## Gameplay

**Flow:** Main Menu → Match → Victory or Defeat → Repeat/Exit.

- The match runs for `MatchDuration` seconds (`DefenseGameMode`, default 60s).
- `EnemySpawner` spawns enemies on a randomized timer (`SpawnIntervalMin`/`Max`); each enemy's State Tree AI paths toward the level's destination point.
- Every enemy (or other actor) that overlaps the destination counts as a breach; reaching `MaxBreachesAllowed` (default 3) ends the match in defeat. Surviving the full duration is a win.
- **Controls:** `WASD` to move, `mouse` to look, `E` to interact with nearby pickups (weapon pickup, clear-enemies pickup), `left mouse click` to fire the equipped weapon.
- The HUD shows time remaining, breach count, ammo, and the current interaction prompt; a result screen shows the match outcome.
