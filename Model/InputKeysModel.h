//
// Created by Artem on 17.12.2025.
//

#ifndef LABAOOP2_INPUTKEYSMODEL_H
#define LABAOOP2_INPUTKEYSMODEL_H

class InputKeysModel{
public:
    char saveGameKey, confirmActionKey, dismissActionKey, attackKey, spellKey, skipMoveKey, continueKey;

    InputKeysModel(char closeGameKey, char confirmActionKey, char dismissActionKey, char attackKey, char spellKey,
                   char skipMoveKey, char continueKey) : saveGameKey(closeGameKey), confirmActionKey(confirmActionKey),
                                                         dismissActionKey(dismissActionKey), attackKey(attackKey),
                                                         spellKey(spellKey), skipMoveKey(skipMoveKey),
                                                         continueKey(continueKey) {}
};

#endif //LABAOOP2_INPUTKEYSMODEL_H
