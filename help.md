# Binary-to-Hexadecimal Display Driver Lab Guide
*EEL 3705L - Lab 4 Complete Walkthrough*

## 1. Design Context & High-Level Block Diagram

### System Overview
We're building a display driver that sits between an input device (switches) and output device (7-segment display).

```
[Input Device]  ------>  [Display Driver]  ------>  [Output Device]
  (Switches)      4-bit      (Your Logic)     7-bit    (7-Seg Display)
   SW[3:0]        bus         Circuit         signals      HEX0
```

**Components on DE1-SoC:**
- **Input Device**: Slide switches SW[3:0] (4 switches for hex input 0-F)
- **Display Driver**: Your combinational logic circuit
- **Output Device**: 7-segment display HEX0

## 2. System-Level Requirements

### Input Specification
- **Signal**: 4-bit bus to represent hex digits 0-F
- **Range**: 0000₂ to 1111₂ (0 to 15 decimal, 0 to F hex)
- **DE1-SoC Input**: SW[3:0] - slide switches
- **Signal Name**: `hex_input[3:0]`

### Output Specification
- **Display**: 7-segment display (segments a,b,c,d,e,f,g)
- **Active Low**: DE1-SoC displays are active low (0 = ON, 1 = OFF)
- **Signal Names**: `seg_a`, `seg_b`, `seg_c`, `seg_d`, `seg_e`, `seg_f`, `seg_g`

### 7-Segment Display Patterns
```
Hex | Display | Segments (abcdefg)
----|---------|-------------------
 0  |   ███   | 0000001 (only g OFF)
    |  █   █  |
    |  █   █  |
    |   ███   |
    |  █   █  |
    |  █   █  |
    |   ███   |
----|---------|-------------------
 1  |     █   | 1001111 (b,c ON)
    |     █   |
    |     █   |
    |     █   |
    |     █   |
    |     █   |
    |     █   |
----|---------|-------------------
 2  |   ███   | 0010010
    |     █   |
    |     █   |
    |   ███   |
    |  █     |
    |  █     |
    |   ███   |
----|---------|-------------------
And so on for 3,4,5,6,7,8,9,A,b,C,d,E,F...
```

### Pin Assignment Table
| Design Signal | FPGA Signal | FPGA Pin |
|---------------|-------------|----------|
| hex_input[0]  | SW[0]       | PIN_AB12 |
| hex_input[1]  | SW[1]       | PIN_AC12 |
| hex_input[2]  | SW[2]       | PIN_AF9  |
| hex_input[3]  | SW[3]       | PIN_AF10 |
| seg_a         | HEX0[0]     | PIN_AE26 |
| seg_b         | HEX0[1]     | PIN_AE27 |
| seg_c         | HEX0[2]     | PIN_AE28 |
| seg_d         | HEX0[3]     | PIN_AG27 |
| seg_e         | HEX0[4]     | PIN_AF28 |
| seg_f         | HEX0[5]     | PIN_AG28 |
| seg_g         | HEX0[6]     | PIN_AH28 |

## 3. Truth Table (The Heart of the Matter)

| Input (DCBA) | Hex | a | b | c | d | e | f | g | Display |
|--------------|-----|---|---|---|---|---|---|---|---------|
| 0000         | 0   | 0 | 0 | 0 | 0 | 0 | 0 | 1 | ⬜⬜⬜<br>⬜⬛⬜<br>⬜⬜⬜ |
| 0001         | 1   | 1 | 0 | 0 | 1 | 1 | 1 | 1 | ⬛⬛⬜<br>⬛⬛⬜<br>⬛⬛⬛ |
| 0010         | 2   | 0 | 0 | 1 | 0 | 0 | 1 | 0 | ⬜⬜⬜<br>⬛⬛⬜<br>⬜⬜⬜ |
| 0011         | 3   | 0 | 0 | 0 | 0 | 1 | 1 | 0 | ⬜⬜⬜<br>⬛⬛⬜<br>⬜⬜⬜ |
| 0100         | 4   | 1 | 0 | 0 | 1 | 1 | 0 | 0 | ⬛⬜⬛<br>⬛⬛⬜<br>⬛⬛⬛ |
| 0101         | 5   | 0 | 1 | 0 | 0 | 1 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬛<br>⬜⬜⬜ |
| 0110         | 6   | 0 | 1 | 0 | 0 | 0 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬛<br>⬜⬜⬜ |
| 0111         | 7   | 0 | 0 | 0 | 1 | 1 | 1 | 1 | ⬜⬜⬜<br>⬛⬛⬜<br>⬛⬛⬛ |
| 1000         | 8   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬜<br>⬜⬜⬜ |
| 1001         | 9   | 0 | 0 | 0 | 0 | 1 | 0 | 0 | ⬜⬜⬜<br>⬛⬛⬜<br>⬜⬜⬜ |
| 1010         | A   | 0 | 0 | 0 | 1 | 0 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬜<br>⬛⬛⬛ |
| 1011         | b   | 1 | 1 | 0 | 0 | 0 | 0 | 0 | ⬛⬛⬛<br>⬜⬛⬛<br>⬜⬜⬜ |
| 1100         | C   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | ⬜⬜⬜<br>⬜⬛⬛<br>⬛⬛⬛ |
| 1101         | d   | 1 | 0 | 0 | 0 | 0 | 1 | 0 | ⬛⬛⬜<br>⬜⬛⬜<br>⬜⬜⬜ |
| 1110         | E   | 0 | 1 | 1 | 0 | 0 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬛<br>⬜⬜⬜ |
| 1111         | F   | 0 | 1 | 1 | 1 | 0 | 0 | 0 | ⬜⬜⬜<br>⬜⬛⬛<br>⬛⬛⬛ |

*Note: 0 = segment ON (active low), 1 = segment OFF*

## 4. Testing Plan

### Simulation Testing
1. **Input Vectors**: Test all 16 combinations (0000 to 1111)
2. **Expected Outputs**: Verify each produces correct 7-segment pattern
3. **Edge Cases**: Pay special attention to letters A,b,C,d,E,F

### Hardware Testing
1. **Sequential Test**: Set switches to each hex value 0-F
2. **Visual Verification**: Confirm display shows correct digit/letter
3. **Random Test**: Try random switch combinations

## 5. Karnaugh Maps for Minimization

### For Segment A:
```
     CD
AB   00  01  11  10
00   0   1   0   0   (0,2,3,5,6,7,8,9,A,C,E,F)
01   1   0   0   1
11   0   1   0   0
10   0   0   0   0
```

**Segment A (active low) = D'C'B'A' + D'CBA' + DCBA + DC'BA' + ...**

*Continue this process for segments B through G*

## 6. Minimum SOP Implementation

After K-map minimization, you'll get something like:
- **seg_a** = f(D,C,B,A) - minimized Boolean expression
- **seg_b** = f(D,C,B,A) - minimized Boolean expression
- ... and so on for each segment

## 7. Quartus Implementation Steps

### Creating the Schematic
1. **New Project**: Create meaningful project name (e.g., "hex_to_7seg_driver")
2. **Input Bus**: Place input pin, set as bus H[3..0]
3. **Output Pins**: Seven individual output pins (seg_a through seg_g)
4. **Logic Gates**: Implement your minimized SOP equations using AND, OR, NOT gates
5. **Connections**: Use net labels instead of direct wiring for cleaner design

### Pin Assignment
Use the Assignment Editor in Quartus:
- Assign H[0] to PIN_AB12 (SW[0])
- Assign H[1] to PIN_AC12 (SW[1])
- Assign H[2] to PIN_AF9 (SW[2])
- Assign H[3] to PIN_AF10 (SW[3])
- Assign outputs to HEX0[0] through HEX0[6]

## 8. Common Pitfalls & Pro Tips

### Pitfalls to Avoid:
- **Active Low Confusion**: Remember DE1-SoC displays are active LOW
- **Bus Indexing**: H[3] is MSB, H[0] is LSB
- **Pin Assignment**: Double-check pin numbers in DE1-SoC manual

### Pro Tips:
- **Test Incrementally**: Verify each segment independently
- **Use Hierarchy**: Create symbol for your module for reuse
- **Document Everything**: Your future self will thank you
- **Visual Debug**: Use LEDs to debug intermediate signals

## 9. Expected Results

When working correctly:
- Switch pattern 0000 → Display shows "0"
- Switch pattern 0001 → Display shows "1"
- Switch pattern 1010 → Display shows "A"
- Switch pattern 1111 → Display shows "F"

## Conclusion

This lab teaches you the complete digital design flow from specification to hardware implementation. You're essentially building a lookup table in hardware - pretty elegant when you think about it!

Remember: The goal isn't just to make it work, but to understand *why* it works. Each step builds your digital design intuition.