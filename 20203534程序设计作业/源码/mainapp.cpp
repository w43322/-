#include"mainapp.h"
const int argumentCount=2;//°´Å¥ÊýÁ¿
void mainApp::run()
{
    init();
    int cmd=mainWindow.getCmd(argumentCount);
    processCmd(cmd);
}

void mainApp::processCmd(int cmd)
{
    switch(cmd)
    {
        case 0:
        {
            goBack();
            break;
        }
        case 1:
        {
            login();
            run();
            break;
        }
        default:
        {
            goBack();
            break;
        }
    }
}

void mainApp::goBack()
{
    printf("--exiting--\n");
    mainWindow.close();
}

void mainApp::login()
{
    printf("--entering login--\n");
    logIn runLogin;
    runLogin.run();
}

void mainApp::init()
{
    mainWindow.init();
    mainWindow.drawButtons(argumentCount,"Exit","Login");
}
