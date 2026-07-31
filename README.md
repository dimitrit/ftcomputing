# fischertechnik Computing

The fischertechnik Computing range, which was available from the mid 1980s until
the early 2000s included the fischertechnik Computing interface, construction sets
and software. This repository includes example applications for some these
constructionsets.

# fischertechnik computing interface

From the mid-1980s to the early 1990s fischertechnik produced interfaces for
computers from a range of manufacturers (including Apple, Commodore and Schneider)
to allow technical models to be controlled by a computer.[^1]

The fischertechnik interface provides the following functions:[^2]

* the ability to control fischertechnik motors, lamps, electromagnets, etc
* check the state of up to eight push buttons or switches
* read the values of up to two potentiometers or other variable signal sources

## Connecting the Interface

In addition to interfaces for specific computers, fischertechnik also released
the fischertechnik Universal and CVK Computing Interfaces. These 'generic' interfaces
supported a wider range of systems by means of a small adapter between the computing
interface and target computer system.

ftPAL is a simple adapter that allows the fischertechnik Universal and CVK Computing
Interfaces to be connected to the PAL-1 RIOT Expansion Module or the PAL-2 Versatile
Interface.[^3][^4]

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

### PAL-2 Versatile Interface Configuration

The ftcomputing library requires the PAL-2 Versatile Interface address select jumper to be set to 16XX.

## fischertechnik Computing Software

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