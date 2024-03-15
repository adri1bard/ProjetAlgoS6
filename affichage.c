void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; 
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(20);
			
			break;
		
		case Temporisation:
			
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			
			effaceFenetre (239, 239, 239);
			
			client2();
			nouvelleligne();
			client6();
			client7();
			supprimer();
			break;
			
		case BoutonSouris:
		
				if (etatBoutonSouris() == GaucheAppuye){
				if(abscisseSouris()<largeurFenetre()/1.5 && abscisseSouris()>largeurFenetre()/3.5 && ordonneeSouris()< hauteurFenetre()/3 && ordonneeSouris()>hauteurFenetre()/5)
				
				{
				afficherBDD();
				}
				
				else if (abscisseSouris()<largeurFenetre()/1.5 && abscisseSouris()>largeurFenetre()/3.5 && ordonneeSouris()<hauteurFenetre()/1.9 && ordonneeSouris()>hauteurFenetre()/2.5)
				{
				ajouterLigneDansBDD();
				}
				else if (abscisseSouris()<largeurFenetre()/1.5 && abscisseSouris()>largeurFenetre()/3.5 && ordonneeSouris()<hauteurFenetre()/7 && ordonneeSouris()>hauteurFenetre()/40)
				{
				supprimerMaladieBDD();
				}
				else if (abscisseSouris()<largeurFenetre()/1.5 && abscisseSouris()>largeurFenetre()/3.5 && ordonneeSouris()<  hauteurFenetre()/1.12 && ordonneeSouris()>hauteurFenetre()/1.3)
				{
				printf("ok\n");
				}

		}
					
			/*else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}*/
			break;
		case Redimensionnement: 
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}


void client2()
{
	couleurCourante(182,255,250);
	rectangle(largeurFenetre()/3.5, hauteurFenetre()/5, largeurFenetre()/1.5, hauteurFenetre()/3);
	couleurCourante(0,0,0);
	afficheChaine("Afficher BDD", 20, largeurFenetre()/2.6, hauteurFenetre()/3.9);	
}

void supprimer()
{
	couleurCourante(182,225,220);
	rectangle(largeurFenetre()/3.5, hauteurFenetre()/40, largeurFenetre()/1.5, hauteurFenetre()/7);
	couleurCourante(0,0,0);
	afficheChaine("Supprimer une maladie", 20, largeurFenetre()/3.1, hauteurFenetre()/15);	
}



void nouvelleligne()
{
	couleurCourante(128,228,255);
	rectangle(largeurFenetre()/3.5, hauteurFenetre()/2.5, largeurFenetre()/1.5, hauteurFenetre()/1.9);
	couleurCourante(0,0,0);
	afficheChaine("Completer BDD", 20, largeurFenetre()/2.6, hauteurFenetre()/2.2);	
}

void client6()
{
	couleurCourante(0,200,200);
	rectangle(largeurFenetre()/3.5, hauteurFenetre()/1.7, largeurFenetre()/1.5, hauteurFenetre()/1.4);
	couleurCourante(0,0,0);
	afficheChaine("Trouver des symptomes", 19, largeurFenetre()/3.1, hauteurFenetre()/1.55);		
}

void client7()
{
	couleurCourante(104,126,255);
	rectangle(largeurFenetre()/3.5, hauteurFenetre()/1.3, largeurFenetre()/1.5, hauteurFenetre()/1.12);
	couleurCourante(0,0,0);
	afficheChaine("Trouver des maladies", 19, largeurFenetre()/3.1, hauteurFenetre()/1.22);	
}

