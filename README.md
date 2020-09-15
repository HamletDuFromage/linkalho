![License](https://img.shields.io/badge/License-GPLv3-blue.svg) [![GitHub release](https://img.shields.io/github/release/rdmrocha/linkalho.svg)](https://github.com/rdmrocha/linkalho/releases/latest/) [![Github all releases](https://img.shields.io/github/downloads/rdmrocha/linkalho/total.svg)](https://GitHub.com/rdmrocha/linkalho/releases/latest/)


# Linkalho

Linkalho is an homebrew app that will link NNID accounts offline. It links (or unlinks) <b>existing</b> accounts so you won't lose your saves.
This app does not create a new account. If you create a new account and want to link it, just re-run the app.

<p align="center"><img src="https://raw.githubusercontent.com/rdmrocha/linkalho/master/icon.jpg"></p>


## Usage
- Place the .nro file in the `/switch/linkalho` folder of your SDcard.
- Go to the homebrew app and run Linkalho


### Link all accounts
Will link all accounts on the console. If any of the existing accounts is already linked, it will be re-linked.
This operation creates a backup in `/switch/linkalho/backups`

### Unlink all accounts
Will remove all NNID linking from any accounts on the console regardless of the NNIDs being officially linked or not.
This operation creates a backup in `/switch/linkalho/backups`

### Restore backup
Restores any previous state from a backup file. The file must be places in `/switch/linkalho/restore/restore.zip`
This operation creates a backup in `/switch/linkalho/backups`

## Screenshots
<p align="center"><img src="https://raw.githubusercontent.com/rdmrocha/linkalho/master/raw/screenshot1.jpg"></p>
<p align="center"><img src="https://raw.githubusercontent.com/rdmrocha/linkalho/master/raw/screenshot2.jpg"></p>
<p align="center"><img src="https://raw.githubusercontent.com/rdmrocha/linkalho/master/raw/screenshot3.jpg"></p>
<p align="center"><img src="https://raw.githubusercontent.com/rdmrocha/linkalho/master/raw/screenshot4.jpg"></p>

## Credits
  - [devkitPro](https://devkitpro.org) for the toolchain!
  - [natinusala (lib borealis)](https://github.com/natinusala/borealis) for the amazing library that mimicks the Switch's original UI and UX
  - [sebastiandev (zipper wrapper for minizip)](https://github.com/sebastiandev/zipper/) for their nice wrapper to the minizip
  - [Kronos2308](https://github.com/Kronos2308) for the help in the initial phases of research.
  - **stick2target** for the beta testing and for supplying crucial files that helped in the creation of the generators.
  - **boredomisacrime** for the beta testing.
