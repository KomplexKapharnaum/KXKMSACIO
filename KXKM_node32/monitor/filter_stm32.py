from platformio.public import DeviceMonitorFilterBase


class Stm32(DeviceMonitorFilterBase):
    NAME = "stm32"

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        print("Demo filter is loaded")

    def rx(self, text):
        if text.startswith("#"): return ''
        return text

    def tx(self, text):
        # print(f"Sent: {text}\n")
        return text