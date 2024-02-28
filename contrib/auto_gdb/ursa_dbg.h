#!/usr/bin/env bash
# use testnet settings,  if you need mainnet,  use ~/.dashcore/dashd.pid file instead
export LC_ALL=C

ursa_pid=$(<~/.ursacore/testnet3/ursa.pid)
sudo gdb -batch -ex "source debug.gdb" ursad ${ursa_pid}
