#!/usr/bin/python
import bluetooth

nearby_devices = bluetooth.discover_devices(
        duration=10, lookup_names=True, flush_cache=True, lookup_class=False)
print("found %d devices" % len(nearby_devices))

for addr, name in nearby_devices:
    print("  %s - %s" % (addr, name))
