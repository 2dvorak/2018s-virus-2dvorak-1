#!/bin/bash
make clean
make
cd bin/

echo "####### [TEST] Testing Elfluenza(the virus)"
OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim ELF header before Elfluenza : "
PRINT=$MSG$OUTPUT
echo $PRINT

echo "Executing Elfluenza(the virus)"
./elfluenza

OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim ELF header after Elfluenza : "
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "ac 3d c0 de" ]; then
	echo "####### [FAIL] Elfluenza failed, Victim not infected"
	exit 1
fi
echo -e "####### [PASS] Victim infected successfully by Elfluenza\n\n"

echo "####### [TEST] Testing Victim(infected)"
echo "Test Victim(infected) to 'ls' copied from /bin/ls"
cp /bin/ls .

OUTPUT="$(readelf -h ls | grep Magic | tail -c 19 | head -c 11)"
MSG="ls ELF header before Victim(infected) : "
PRINT=$MSG$OUTPUT
echo $PRINT

MSG="Executing Victim(infected) : "
OUTPUT="$(./victim)"
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "hello" ]; then
	echo "####### [FAIL] Elfluenza failed, Victim not working"
	exit 1
fi

OUTPUT="$(readelf -h ls | grep Magic | tail -c 19 | head -c 11)"
MSG="ls ELF header after Victim(infected) : "
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "ac 3d c0 de" ]; then
	echo "####### [FAIL] Victim(infected) failed, ls not infected"
	exit 1
fi
echo -e "####### [PASS] ls infected successfully by Victim(infected)\n\n"

echo "####### [TEST] Testing Elfpacito(the vaccine)"
OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim ELF header before Elfpacito(the vaccine) : "
PRINT=$MSG$OUTPUT
echo $PRINT

echo "Executing Elfpacito(the vaccine)"
./elfpacito

OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim ELF header after Elfpacito(the vaccine) : "
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "5a fe c0 de" ]; then
	echo "####### [FAIL] Elfpacito failed, Victim not cured"
	exit 1
fi

echo "Copying /bin/ls again to test if Victim(cured) stops malicious operation"
cp /bin/ls .

OUTPUT="$(readelf -h ls | grep Magic | tail -c 19 | head -c 11)"
MSG="ls ELF header before Victim(cured) : "
PRINT=$MSG$OUTPUT
echo $PRINT

MSG="Executing Victim(cured) : "
OUTPUT="$(./victim)"
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "hello" ]; then
	echo "####### [FAIL] Elfpacito failed, Victim not working"
	exit 1
fi

OUTPUT="$(readelf -h ls | grep Magic | tail -c 19 | head -c 11)"
MSG="ls ELF header after Victim(cured) : "
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "00 00 00 00" ]; then
	echo "####### [FAIL] Elfpacito failed, Victim not cured"
	exit 1
fi
echo -e "####### [PASS] Victim cured successfully by Elfpacito\n\n"

OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim(cured) ELF header before Elfluenza : "
PRINT=$MSG$OUTPUT
echo $PRINT

echo "Executing Elfluenza(the virus) again to test Victim(cured) get immune to virus"
./elfluenza

OUTPUT="$(readelf -h victim | grep Magic | tail -c 19 | head -c 11)"
MSG="Victim(cured) ELF header after Elfluenza : "
PRINT=$MSG$OUTPUT
echo $PRINT
if [ "$OUTPUT" != "5a fe c0 de" ]; then
	echo "####### [FAIL] Elfpacito failed, Victim not immuned"
	exit 1
fi
OUTPUT="$(./victim)"
if [ "$OUTPUT" != "hello" ]; then
	echo "####### [FAIL] Elfluenza failed, Victim not working after trying to infect after cured"
	exit 1
fi
echo -e "####### [PASS] Victim immuned successfully by Elfpacito\n\n"

echo "####### All Test Passed!!"
cd ..