/*
 * \file GuiLogin.h
 *
 *  Created on: \date 13 avr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef GUI_LOGIN_H_
#define GUI_LOGIN_H_

#include "Interface/Interface.h"

#include "GameState/GameStateManager.h"

enum eventlogin
{
	CONNEXIONBOUTON = 1,
	QUITBOUTON
};

/*
 *
 */
class GuiLogin : public GuiInterface
{
public:
	GuiLogin(ControleInterface * controleInterface);
	virtual ~GuiLogin();

    bool connexionButton(const CEGUI::EventArgs &e);
    bool quitterButton(const CEGUI::EventArgs &e);

    void switchEditBox();

    const char * getLogin();
    const char * getPassword();



    void update();

private:
    ControleInterface * controleInterface ;

};

#endif /* GUI_LOGIN_H_ */
