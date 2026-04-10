#include "Pass.hpp"

void Pass::execute(Client &client, std::string &input)
{
    std::cout<<"dans pass ligne a traiter : |"<< input<<"|"<<std::endl;
    std::cout<<"dans pass le password attendu est : |"<< _serverPassword<<"|"<<std::endl;
    //verifier la validite de la ligne 
    std::string password;//set le password envoye en arg de la commande
    if (client.isAuthenticated())
    {
        //set dant loutput du client un message already registred
        // client.addToOutput("le message");
        //        462     ERR_ALREADYREGISTRED
                        // ":You may not reregister"
        // :<servername> 462 <nick> :You may not reregister\r\n 
        return ;
    }
    if (_serverPassword == input) //a voir si le password est autorise a contenir des expaces par ex
    {
        std::cout<<"super dans pass le mdp est correct"<<std::endl;
        client.setHasValidPassword(true);
        return ;
    }
    std::cout<<"pas super du tout dans pass le mdp est incorrect"<<std::endl;
    //set dans l'output du clietn message d'erreur invalide password
}
