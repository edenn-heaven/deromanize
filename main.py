import keyboard

enabled = False

def toggle() :
    global enabled
    enabled = not enabled

keyboard.add_hotkey("f8", toggle)
keyboard.wait()