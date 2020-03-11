def main():
    SAMPLES_PER_AXIS = 5
    NORMALISED_RANGE = 0.5

    for x in range(0, SAMPLES_PER_AXIS):
        for y in range(0, SAMPLES_PER_AXIS):
            x_normalised = ((x / float(SAMPLES_PER_AXIS - 1)) * 2.0 - 1.0) * NORMALISED_RANGE
            y_normalised = ((y / float(SAMPLES_PER_AXIS - 1)) * 2.0 - 1.0) * NORMALISED_RANGE

            print(str(x_normalised) + ", " + str(y_normalised))

if __name__ == '__main__':
    main()