import pickle, string, sys, getopt


def encoder(inputFile, encodedFile):
    tam_dict = len(string.printable)

    # initialize dictionary
    dictionary = dict()
    i = 0
    for char in string.printable:
        dictionary[char] = i
        i += 1

    result = []
    old_encoding = ""

    with open(inputFile, 'r') as f:
        data = f.read()
        for c in data:
            if c not in string.printable or c == '\r':
                if c != '\r':
                    print("hum: ",c)
                continue
            encoding = old_encoding + c
            if encoding in dictionary:
                if c == old_encoding:
                    result.append(dictionary[old_encoding])
                    old_encoding = c
                else:
                    old_encoding = encoding
            else:
                # if old_encoding != "":
                result.append(dictionary[old_encoding])
                dictionary[encoding] = tam_dict
                tam_dict += 1
                old_encoding = c
        result.append(dictionary[c])

    # print(result)
    # print(dictionary)

    with open(encodedFile, 'wb+') as out:
        pickle.dump(result, out, pickle.HIGHEST_PROTOCOL)


def decoder(encodedFile, decodedFile):
    tam_dict = len(string.printable)

    # initialize dictionary
    dictionary = dict()
    i = 0
    for char in string.printable:
        dictionary[i] = char
        i += 1

    char = ""
    result = ""
    old_encoding = ""

    with open(encodedFile, 'rb') as f:
        str = ""
        data = pickle.load(f)
        for encoding in data:
            if encoding in dictionary:
                result += dictionary[encoding]
                c = dictionary[encoding][0]
                if old_encoding + c not in dictionary.values():
                    dictionary[tam_dict] = old_encoding + c[0]
                    tam_dict += 1
                    old_encoding = dictionary[encoding]
                else:
                    old_encoding = dictionary[encoding]
            else:
                if encoding > tam_dict:
                    print("ERRO")
                    # print(dictionary)
                    # print(encoding)
                    # print(result)
                    sys.exit(0)
                dictionary[tam_dict] = old_encoding[-1]+old_encoding[-1]
                tam_dict += 1
                result += dictionary[encoding]
                old_encoding = old_encoding[-1]

    # print(dictionary)

    with open(decodedFile, 'w+') as out:
        out.write(result)


def main(argv):
    inputFile = ''
    encodedFile = ''
    decodedFile = ''

    try:
        opts, args = getopt.getopt(argv,"hi:e:d:",["ifile=","efile=","dfile="])
    except getopt.GetoptError:
        print ('lzw.py -i <toencodefile> -e <encodedfile> -d <decodedfile>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print ('lzw.py -i <toencodefile> -e <encodedfile> -d <decodedfile>')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            inputFile = arg
        elif opt in ("-e", "--efile"):
            encodedFile = arg
        elif opt in ("-d", "--dfile"):
            decodedFile = arg
    print ('Input file is "', inputFile)
    print ('Encoded file is "', encodedFile)
    print ('Decoded file is "', decodedFile)

    print ('Compressing')
    encoder(inputFile, encodedFile)
    print ('Decompressing')
    decoder(encodedFile, decodedFile)
    print ('All done!')


if __name__ == '__main__':
    main(sys.argv[1:])
