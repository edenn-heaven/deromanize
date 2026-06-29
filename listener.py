from app.translit import transliterate
import keyboard

buffer = ""
enabled_ref = None

def set_enabled_ref(ref):
    global enabled_ref
    enabled_ref = ref

def on_press(event):
    global buffer

    if enabled_ref is None or not enabled_ref():
        return

    key = event.name

    if key == "backspace":
        buffer = buffer[:-1]
        return

    if key in ["space", "enter"]:
        if buffer:
            print(transliterate(buffer))
        buffer = ""
        return

    if len(key) == 1:
        buffer += key

def start():
    keyboard.on_press(on_press)
    print("Deromanize successfully launched")