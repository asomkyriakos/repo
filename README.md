- Compile with:
g++ -std=c++17 -Wall main.cpp CreateWorld.cpp GridWorld.cpp -o simulation
- Execute with:
./simulation --seed 42 --dimX 10 --dimY 10 --numMovingCars 3 --numMovingBikes 2 --numParkedCars 4 --numStopSigns 2 --numTrafficLights 2 --gps 2 3 7 8
- For help run:
./simulation --help
- Also a make file:
make 
- And to clear cache of executables:
make clean


// TO BE DELETED //
Πρόσθεσα στο makefile το αρχείο, στη main και το SelfDrivingCar τη βιβλιοθήκη.
Στη main έχω προσθέσει κάτι λίγο για έλεγχο.

Μου βγάζει δύο warnings μόνο. Μήπως να αλλάξουμε στο CreatWorld.cpp το char direction; σε char direction = 'N'; στις γραμμές 33,53.

// Νεες Αλλαγες //
Εκανα αλλαγες σε ολο τον κωδικα, ακομα δουλευω στην συγχωνευση ολων των δεδωμενων στην fuseSensorData στην τελευταια function. Πειραξα τα sensors για να επιστρεφουν τα data που επιτρεπεται το καθενα να επιστρεφει(καμερα επιστρεφει ολα τα δεδομενα, ρανταρ επιστρεφει και ταχυτητα και direction)
Εφτιαξα την υπαρξη του αυτοκινητου στον χαρτη
Μενει να κανω την συναρτηση και την λογικη αποφασης κινησης του αυτοκινητου
#Cutting Arteries

//Νεες *παλι* αλλαγες //
εφτιαξε ενα απλο decision making
μενει να του βαλω να επιλεγει αν θα επιταχυνει, κρατησει ταχυτητα ή αποταχυνει
