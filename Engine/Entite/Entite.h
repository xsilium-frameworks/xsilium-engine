/*
 * \file Entite.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef ENTITE_H_
#define ENTITE_H_

#include <string>

/*
 *
 */
class Entite {
public:
	Entite();
	virtual ~Entite();

	void setVieEntite(int Vie);
	int getVieEntite();
	void setNom(std::string nom);
	std::string * getNom();

protected:
	int vieEntite;
	std::string * nom;


};

#endif /* ENTITE_H_ */
