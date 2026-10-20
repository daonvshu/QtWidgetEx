# QtWidgetEx
qt widget values setter extension

The Qt Designer plugin is enabled by default and requires the selected Qt SDK's
`UiPlugin` development module. If the module is unavailable, CMake prints a status
message and skips the plugin while continuing to build the widget library.

To explicitly disable the plugin, add `-DWIDGETEX_BUILD_PLUGIN=OFF` to the CMake
configuration options. When the plugin is skipped or disabled, build the
`qtwidgetex` target instead of `QtWidgetExPlugin`.

Native Windows builds copy the plugin into the selected Qt SDK's Designer plugin
directory. On other platforms and when cross-compiling, the plugin remains in the
build directory for manual deployment.
