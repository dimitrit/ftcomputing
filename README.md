# fischertechnik computing interface

The fischertechnik computing interface allows technical models to be controlled by a computer.[^1]

fischertechnik computing includes the fischertechnik computing kit, the fischertechnik computing construction sets, the fischertechnik computing interfaces and software.

The fischertechnik interface provides the following functions:[^2]

* the ability to control fischertechnik motors, lamps, electromagnets, etc
* check the state of up to eight push buttons or switches
* read the values of up to two potentiometers or other variable signal sources

## Connecting the Interface

Between the mid-1980s and early 1990s fischertechnik produced computing interfaces for a range of computer systems, including Apple, Commodore and Schneider. In addition to these dedicated interfaces, fischertechnik also released universal interfaces. While dedicated interfaces could be plugged in to the respective computers directly, the fischertechnik Universal and CVK Computing Interfaces required adapters between the interface connector and target computer systems.

ftPAL is a simple adapter that allows the fischertechnik Universal and CVK Computing Interfaces to be connected to the PAL-1 RIOT Expansion Module or the PAL-2 Versatile Interface.[^3][^4]

The ftPAL adapter implements the same logical connections as the fischertechnik Commodore 64 adapter:[^5]

| PAL VIA  | ft Interface        | Description |
| :------: | :-----------------: | :---------: |
| PB0      | LOAD_OUT            | Signal digital output |
| PB1      | LOAD_IN             | Signal digital input |
| PB2      | DATA_OUT            | Digital data output  stream |
| PB3      | CLOCK               | Data transfer clock |
| PB4      | TRIGGER_X           | Trigger analog input X |
| PB5      | TRIGGER_Y           | Trigger analog input Y |
| PB6      | COUNT_IN            | Analog data input pulses |
| PB7      | DATA_IN<sup>*</sup> | Digital data input stream |

<sup>*</sup>The software in this repository expects the `C64` to be jumper to be installed in `Data Input Select`

## fischertechnik computing Software

The code in this repository requires the compilers, linkers and other tools provided by the cc65 cross development package.[^6] Note that the cc65 environment *must* include runtime library support for the KIM-1 system.

While the software in this repository is specifically written for the PAL-2 with Versatile Interface expansion card, it should be relatively straight forward to port it to other 6502 based systems.

### Building the applications on macOS 15 (Sequoia)

Building the code on macOS may require the `CC65_HOME' environment variable to be set, for example:

```
export CC65_HOME=/usr/local/share/cc65
```

[^1]: fischertechnik, _‘Robots, Automats and graphic units to build yourself’_, 1985, <https://docs.fischertechnikclub.nl/info2/1985.pdf> [accessed 1 September 2025]
[^2]: fischertechnik, _‘Computing Interface’_, N.D., <https://docs.fischertechnikclub.nl/computing/39484.pdf> [accessed 30 August 2025].
[^3]: Liu Ganning, _‘RIOT EXPANSION’_, 2021, <http://pal.aibs.ws/assets/RIOT_expansion_manual.pdf> [accessed 26 January 2024].
[^4]: Dimitri Theulings, _PAL-2 Versatile Interface_, 2026
[^5]: R Trapp, _‘ft66843 Schematic’_, 2017, <https://ftcommunity.de/knowhow/computing/computing_interfaces/ft66843_schematic.pdf> [accessed 30 August 2025].
[^6]: Ullrich von Bassewitz and others, _cc65, the 6502 C compiler, 2026, <https://cc65.github.io/> [accessed 30 July 2026]