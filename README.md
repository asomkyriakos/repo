# Self-Driving Car

## Build

Compile with:
```sh
make
```

Clear with
```sh
make clean
make clean-all
```

## Usage 

Execute with:
```sh
./simulation --'Options'
```
Options:

    - seed num
    - dimX num
    - dimY num
    - numMovingCars num
    - numMovingBikes num
    - numParkedCars num
    - numStopSigns num
    - numTrafficLights num
    - gps num1 num2 num3 num4 ...

For example:
```sh
./simulation --seed 42 --dimX 10 --dimY 10 --numMovingCars 3 --numMovingBikes 2 --numParkedCars 4 --numStopSigns 2 --numTrafficLights 2 --gps 2 3 7 8
```

For help run: 
```sh
./simulation --help
```

## Info

Ο χάρτης αποθηκεύεται με μορφή vector το οποίο περιέχει vector ενσωματομένο σε ένα ακομή vector με τους τύπους δεδομένων των κλάσεων.
Ακόμα τα δεδομένα τυπώνονται στην οθόνη καλώντας τις getGlyph() μεθόδους από κάθε αντικείμενο που βρίσκεται στον χάρτη.
Οι sensors τραβάνε δεδόμενα από τον χάρτη με βάση τις οδηγίες που δώθηκαν και τα αξιοποιούν συναρτήσεις που ενώνουν τα δεδομένα για περαιτέρο χρήση.
Τα ενωμένα πλέον δεδομένα χρησιμοποιούνται από μια συνάρτηση που ελέγχει τα δεδόμενα και αποφασίζει την κατεύθυνση και μεταβολή της ταχύτητας του αυτοκινήτου.




## Authors
**Ονοματεπώνυμο:** Ασώματος Κυριάκος 

**Αριθμός Μητρώου:** 1115 2024 00010

**Ονοματεπώνυμο:** Μπαλή Νεφέλη-Ειρήνη

**Αριθμός Μητρώου:** 1115 2024 00134
