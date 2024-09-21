#!/bin/bash
set -e


SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
echo ""

echo "Flashing board... "
echo ""

cd "${SCRIPTPATH}"
dslite.sh -c user_files/configs/cc1352p1f3.ccxml -l user_files/settings/generated.ufsettings -e -f -v edge_impulse_firmware.out
cd -

echo ""
echo "Flashed your TI LaunchXL development board."
echo "To set up your development with Edge Impulse, run 'edge-impulse-daemon'"
echo "To run your impulse on your development board, run 'edge-impulse-run-impulse'"
