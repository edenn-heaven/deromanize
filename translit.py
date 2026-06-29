rules = {
    "shch": "щ",
    "zh": "ж",
    "kh": "х",
    "ch": "ч",
    "sh": "ш",
    "yu": "ю",
    "ya": "я",
    "yi": "ы",
        
    "a": "а",
    "b": "б",
    "v": "в",
    "g": "г",
    "d": "д",
    "e": "е",
    "ë": "ё",
    "z": "з",
    "i": "и",
    "y": "й",
    "k": "к",
    "l": "л",
    "m": "м",
    "n": "н",
    "o": "о",
    "p": "п",
    "r": "р",
    "s": "с",
    "t": "т",
    "u": "у",
    "f": "ф",
    "c": "ц",
    "'": "ь",
    "è": "э",
}

def transliterate (text) :
    for latin, cyr in rules.items():
        text = text.replace(latin, cyr)
    return text