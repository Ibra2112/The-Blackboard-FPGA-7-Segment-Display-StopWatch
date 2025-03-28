# Seven Segment Display Counter with Button Control (FPGA Embedded C)

This project demonstrates a simple counter implemented in C for an FPGA using memory-mapped I/O to control a seven-segment display. The counter starts, pauses, and resets based on button input.

## 📦 Overview

This program is written for an FPGA board that maps:
- A seven-segment display controller to memory address `0x43c10000`
- Push buttons to address `0x41200000`

It increments a 4-digit BCD counter (0–9999) and displays it on the seven-segment display.

## 🧠 Features

- **4-digit counter** displayed on a seven-segment display.
- **Start/Pause/Reset control** using three hardware buttons:
  - **Button 0**: Pause counting
  - **Button 1**: Resume counting
  - **Button 2**: Reset to 0000
- **Memory-mapped register control** for direct interaction with FPGA peripherals.

## 🧾 Register Map

| Register       | Address      | Description |
|----------------|--------------|-------------|
| `SEG_CTL`      | `0x43c10000` | Control register. Bit 0 = Enable, Bit 1 = Mode (0 = default) |
| `SEG_DATA`     | `0x43c10004` | Display register. Each byte = BCD digit. `0x80808080` enables segments |
| `Button_DATA`  | `0x41200000` | Lower 4 bits used. Buttons 0, 1, 2 control pause, resume, and reset |

## 🕹️ Controls

| Button     | Bit | Function      |
|------------|-----|---------------|
| Button 0   | 0   | Pause counter |
| Button 1   | 1   | Resume counter |
| Button 2   | 2   | Reset to 0000  |

## 🛠️ Dependencies

This program requires:
- Standard C libraries (`stdint.h`, `stdio.h`)
- A `sleep` utility (from Xilinx's `sleep.h` or equivalent)

Ensure you have the FPGA's memory mapping configured correctly to use the provided addresses.

## 🧮 Counter Logic

Each digit is represented using an 8-bit variable:
- `tempVar0`: 1s place
- `tempVar1`: 10s place
- `tempVar2`: 100s place
- `tempVar3`: 1000s place

When the count reaches `9999`, it rolls over back to `0000`.

## 💡 How It Works

1. The display is enabled via `SEG_CTL = 0x01`.
2. The counter starts only after Button 1 is pressed.
3. Button presses are continuously checked to pause, resume, or reset the counter.
4. `SEG_DATA` is updated with the packed BCD digits and segment control bits.
5. Counting pauses when requested and resumes based on button input.

## 🚀 Getting Started

1. Clone the repo and load the C code into your Xilinx SDK or any supported toolchain.
2. Connect your seven-segment display and push buttons to the specified memory-mapped addresses.
3. Compile and deploy to the FPGA.
4. Use the buttons to control the counter as described above.
