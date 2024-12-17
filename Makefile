################
### MAKEFILE ###
################

##  @file Makefile
#	@author Emilien Sanchez (emilien.sanchez@univ-tlse3.fr)
#	@brief Makefile executant toutes les commandes décrites dans le README.md
#
#	@version 0.4
#	@date 2023-12-04
# 
#	@copyright Copyright (c) 2023
#
##


# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Werror
NOM_RENDU = ARCHIVE_CC4#LE_NOM_DU_CC


# Fichiers sources
SRC_DIR = ./src
TEST_DIR = ./tests

HEADER = ./src/$(wildcard *.h)

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/sha256.c $(SRC_DIR)/sha256_utils.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c $(SRC_DIR)/verify_vote.c $(SRC_DIR)/uninominale.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/list_circuit.c $(SRC_DIR)/condorcet_minimax.c $(SRC_DIR)/condorcet_pairs.c  $(SRC_DIR)/JugementMajoritaire.c $(SRC_DIR)/condorcet_schulze.c 

SRC_FILES_TESTS_VERIF = $(TEST_DIR)/tests_verification.c $(SRC_DIR)/sha256.c $(SRC_DIR)/sha256_utils.c $(SRC_DIR)/verify_vote.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/list.c $(SRC_DIR)/csv.c

SRC_FILES_TESTS_UNI = $(TEST_DIR)/tests_uninominale.c  $(SRC_DIR)/list.c $(SRC_DIR)/uninominale.c $(SRC_DIR)/utils_sd.c

SRC_FILES_TESTS_UTILS = $(TEST_DIR)/tests_utils_sd.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c $(SRC_DIR)/list_circuit.c $(SRC_DIR)/utils_sd.c 
SRC_FILES_TESTS_LIST_CIRCUIT = $(TEST_DIR)/tests_circuit.c $(SRC_DIR)/list_circuit.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/csv.c  $(SRC_DIR)/list.c 

SRC_FILES_TESTS_C_PAIRS = $(TEST_DIR)/tests_condorcet_pairs.c $(SRC_DIR)/condorcet_pairs.c  $(SRC_DIR)/list_circuit.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c 
SRC_FILES_TESTS_JM = $(TEST_DIR)/testJM.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c $(SRC_DIR)/JugementMajoritaire.c $(SRC_DIR)/utils_sd.c
SRC_FILES_TESTS_C_MINIMAX =  $(TEST_DIR)/tests_condorcet_minimax.c $(SRC_DIR)/condorcet_minimax.c  $(SRC_DIR)/list_circuit.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c 
SRC_FILES_TESTS_C_SCHULZE =	 $(TEST_DIR)/tests_condorcet_schulze.c $(SRC_DIR)/condorcet_schulze.c  $(SRC_DIR)/list_circuit.c $(SRC_DIR)/utils_sd.c $(SRC_DIR)/csv.c $(SRC_DIR)/list.c

# Executables en sortie

TARGET1 = main

TARGET2 = testsVerification

TARGET3 = testsUninominale
TARGET4 = testsUtilsSd
TARGET5 = testsListCircuit

TARGET6 = testsCondorcetPairs
TARGET7 = testsJugementMajoritaire
TARGET8 = testsCondorcetMinimax
TARGET9 = testsCondorcetSchulze


all : $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9)

$(TARGET1): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET1)

$(TARGET2) : $(SRC_FILES_TESTS_VERIF)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_VERIF) -o $(TARGET2)

$(TARGET3) : $(SRC_FILES_TESTS_UNI)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_UNI) -o $(TARGET3)

$(TARGET4) : $(SRC_FILES_TESTS_UTILS)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_UTILS) -o $(TARGET4)

$(TARGET5) : $(SRC_FILES_TESTS_LIST_CIRCUIT)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_LIST_CIRCUIT) -o $(TARGET5)

$(TARGET6) : $(SRC_FILES_TESTS_C_PAIRS)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_C_PAIRS) -o $(TARGET6)

$(TARGET7) : $(SRC_FILES_TESTS_JM)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_JM) -o $(TARGET7)

$(TARGET8) : $(SRC_FILES_TESTS_C_MINIMAX)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_C_MINIMAX) -o $(TARGET8)

$(TARGET9) : $(SRC_FILES_TESTS_C_SCHULZE)
	$(CC) $(CFLAGS) $(SRC_FILES_TESTS_C_SCHULZE) -o $(TARGET9)

exec : all 
	mkdir -p executables
	cp -rf $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) executables
	rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9)
	
clean:
	rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) executables
	clear

ultraclean: clean
	rm -rf executables
	rm -rf documentation/html/
	clear

doc : $(HEADER)
	@doxygen documentation/doxyfile

deliver : 
	mkdir $(NOM_RENDU)
	cp -r src $(NOM_RENDU)
	cp -r fichiers $(NOM_RENDU) 
	cp -r tests $(NOM_RENDU) 
	cp -r documentation $(NOM_RENDU) 
	rm -rf $(NOM_RENDU)/documentation/html/
	cp -f README.md $(NOM_RENDU)
	cp -f Makefile $(NOM_RENDU)
	zip -r $(NOM_RENDU).zip $(NOM_RENDU)
	rm -rf $(NOM_RENDU)
