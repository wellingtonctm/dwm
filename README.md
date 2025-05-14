# My Custom dwm Build

This is my personalized build of [dwm](https://dwm.suckless.org/), the dynamic window manager from suckless.org.

> This build is based on the original [dwm source code](https://git.suckless.org/dwm/), developed and maintained by the [suckless.org](https://suckless.org/) team.

<!-- ## Features

- **Smart Gaps**: Automatically remove outer gaps when only one window is present.
- **No Borders**: Remove window borders when only one window is visible.
- **Custom Keybindings**: Tailored shortcuts for improved workflow efficiency.
- **Enhanced Layouts**: Additional layouts like centered master and Fibonacci.
- **Systray Support**: Integrated system tray for status icons.
- **Autostart**: Automatically launch applications on startup.

## Applied Patches

- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [noborder](https://dwm.suckless.org/patches/noborder/)
- [systray](https://dwm.suckless.org/patches/systray/)
- [autostart](https://dwm.suckless.org/patches/autostart/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
- [fibonacci](https://dwm.suckless.org/patches/fibonacci/)

## Screenshots

*Include screenshots here to showcase your custom dwm setup.* -->

## Installation

### Dependencies

Ensure you have the following packages installed:

- `libx11-dev`
- `libxft-dev`
- `libxinerama-dev`

### Build and Install

```bash
git clone https://github.com/wellingtonctm/dwm.git
cd dwm
sudo make clean install
```

## Usage

Add the following line to your `.xinitrc` to start dwm using `startx`:

```bash
exec dwm
```

## Configuration

All configurations, including keybindings and appearance settings, are managed in the `config.h` file. After making changes, recompile dwm to apply them:

```bash
sudo make clean install
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

Thanks to the [suckless](https://suckless.org/) community and contributors for their work on dwm and related patches.