# Week 2 — NUCLEO-F401RE Button EXTI + Debounce (one toggle per press)

Board: **NUCLEO-F401RE (STM32F401RE)**

## What it does
- Uses **PC13 (B1 USER button)** as an external interrupt (EXTI).
- Debounces the button in software (30 ms stable time).
- Toggles **LD2 (PA5)** exactly once per press.

## Hardware
- Connect the board to PC using the **ST-LINK USB** port.

## Build & Flash (STM32CubeIDE)
1. Open STM32CubeIDE
2. Import this folder:
   - File → Import… → General → Existing Projects into Workspace
3. Build (hammer)
4. Run/Debug
5. Press USER button → LD2 toggles once per press

<img width="3072" height="4096" alt="image" src="https://github.com/user-attachments/assets/2871c136-121a-4763-9622-8ebeb4789d98" />

<img width="3072" height="4096" alt="image" src="https://github.com/user-attachments/assets/e87679cb-d0ea-44a8-9b6e-1eebdcc81cfc" />
