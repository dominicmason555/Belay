import asyncio
import pynng
from bleak import BleakClient, BleakScanner


ADDRESS = "tcp://127.0.0.1:5432"


async def scan_for_esp():
    print("Scanning...")
    devs = await BleakScanner.discover()
    for dev in devs:
        if "Dasonic" in str(dev.name):
            print(f"Found the ESP: {dev}")
            return BleakClient(dev)


def get_uart(esp):
    for serv in esp.services:
        if serv.description == "Nordic UART Service":
            return serv.characteristics[1]


async def blink(dev, cha):
    print("Server Blinking")
    await dev.write_gatt_char(cha, b"led050500")
    await asyncio.sleep(1)
    await dev.write_gatt_char(cha, b"led050005")
    await asyncio.sleep(1)


async def power_cycle(dev, cha):
    print("Server Power Cycling")
    await dev.write_gatt_char(cha, b"out0")
    await asyncio.sleep(1)
    await dev.write_gatt_char(cha, b"out1")


async def process_msg(msg, dev, cha):
    print(f"Server Received: {msg}")

    if msg == "cycle":
        await power_cycle(dev, cha)
        return "success"

    if msg == "blink":
        await blink(dev, cha)
        return "success"

    print("Unhandled message!")
    return "unhandled"


async def listen_loop(dev, cha):
    survive = True
    with pynng.Rep0(listen=ADDRESS) as sock:
        while survive:
            msg = await sock.arecv_msg()
            content = msg.bytes.decode()
            response = await process_msg(content, dev, cha)
            await sock.asend(response.encode())


async def main():
    esp = await scan_for_esp()
    if esp is None:
        print("Failed to find the esp")
        return
    await esp.connect()
    try:
        uart = get_uart(esp)
        if uart is None:
            print("Failed to find the UART service")
            return
        await listen_loop(esp, uart)
    finally:
        await esp.disconnect()


def belay_entry():
    asyncio.run(main())


if __name__ == "__main__":
    belay_entry()

