prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: ethrpc
Description: Ethereum rpc connector with OOP interface.
URL: https://github.com/devktor/ethrpc
Version: @Eth_Connector_VERSION_MAJOR@.@Eth_Connector_VERSION_MINOR@.@Eth_Connector_VERSION_PATCH@
Libs: -L${libdir} -lethrpc
Cflags: -I${includedir}
