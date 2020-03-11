def main():
    emoji_names = [
        "CRYING_LAUGHTER",
        "HEART_EYES",
        "POOL_OF_TEARS",
        "RED_CHEEKS",
        "SAD",
        "SHADES",
        "SMILE",
        "SMILING_PILE_OF_POO",
        "TEETH",
        "THINKING"
    ]

    orientations = [
        "U",
        "L",
        "D",
        "R"
    ]

    for name in emoji_names:
        for ori in orientations:
            #emojiNames[UNITED_KINGDOM] = "United Kingom";
            full_name = name + "_" + ori
            print("emojiNames[" + full_name + "] = \"" + full_name.lower() + "\";")

if __name__ == '__main__':
    main()