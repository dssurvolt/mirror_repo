#include <iostream>
#include <string>

std::string applyROT13(const std::string& input) {
    std::string result;

    for (char c : input) {
        if (c >= 'a' && c <= 'z') {
            // Décalage pour les lettres minuscules
            result += (c - 'a' + 13) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            // Décalage pour les lettres majuscules
            result += (c - 'A' + 13) % 26 + 'A';
        } else {
            // Conserve les caractères non alphabétiques tels quels
            result += c;
        }
    }

    return result;
}

int main() {
    std::string text;
    std::cout << "Entrez le texte à chiffrer avec ROT13 : ";
    std::getline(std::cin, text);

    std::string encryptedText = applyROT13(text);
    std::cout << "Texte chiffré : " << encryptedText << std::endl;

    return 0;
}


Voici une manière de rédiger cette expérience pour votre CV :

---

**Stage académique**  
- **Participation au développement de l'application Waa** pour Celtiis : contribution à la conception et à la réalisation technique, avec une attention particulière portée à la fonctionnalité et à la satisfaction des utilisateurs.  
- **Amélioration du menu USSD pour Moov** : analyse des retours utilisateurs et optimisation de la navigation pour offrir une expérience fluide et intuitive.  
- Développement de compétences en gestion de projet, collaboration d'équipe et conception centrée sur l'utilisateur.

---

Ce format met en valeur vos contributions et compétences acquises. Vous souhaitez le personnaliser davantage ? 😊🚀
