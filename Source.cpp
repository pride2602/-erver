#include <iostream>
#include "Bible.h"

int TFormMain::analog()
{
    int a;
    for (int i = 0; i < mass; i++)
    {
        if (m[i] == "")
        {
            a = i;
            break;
        }
    }
    return a;
}

void __fastcall TFormMain::ServerSocketClientConnect(TObject* Sender,
	TCustomWinSocket* Socket)
{
	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer1Timer(TObject* Sender)
{

	if (ServerSocket->Socket->ActiveConnections != 0)
		for (int i = 0; i < ServerSocket->Socket->ActiveConnections; i++)
			ServerSocket->Socket->Connections[i]->SendText("8714" + online());
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------


AnsiString TFormMain::online()
{
    char str[500] = "";
    for (int i = 0; i < analog(); i++)
    {
        strcat(str, m[i].c_str());
        strcat(str, ",");
    }
    return str;
}

void __fastcall TFormMain::ServerSocketClientRead(TObject* Sender,
    TCustomWinSocket* Socket)
{
    message = Socket->ReceiveText();
    time = Now().CurrentDateTime();
    if (message.SubString(1, 4).AnsiCompare("6141") == 0)
    {
        m[analog()] = message.SubString(5, message.Length());
        ListBox1->Clear();
        for (int i = 0; i < ServerSocket->Socket->ActiveConnections; i++)
        {
            ListBox1->Items->Add(m[i]);
        }
    }
    else if (message.SubString(1, 4).AnsiCompare("5487") == 0)
    {
        for (int i = 0; i < ServerSocket->Socket->ActiveConnections; i++)
            ServerSocket->Socket->Connections[i]->SendText("8714" + online());
    }
    else if (message.SubString(1, 4).AnsiCompare("3988") == 0)
    {
        nametowho = message.SubString(message.AnsiPos('É') + 1, message.AnsiPos(':') - message.AnsiPos('É') - 1);
        name = message.SubString(5, message.AnsiPos('É') - 5);
        if (nametowho.IsEmpty() == false && (message.SubString(message.AnsiPos(':') + 1, message.Length()).IsEmpty()) == false)
        {
            ServerSocket->Socket->Connections[numer(nametowho)]->SendText("7788" + name + ":" + message.SubString(message.AnsiPos(':') + 1, message.Length()));
            ofstream fout("chat.txt", ios::app);
            fout << time.c_str() << "   " << message.c_str() << endl;
            fout.close();
        }
    }
    else if (message.SubString(1, 4).AnsiCompare("5280") == 0)
    {

        ServerSocket->Socket->Connections[numer(message.SubString(message.Pos('#') + 1, message.Pos('%') - message.Pos('#') - 1))]->SendText(
            "6734" + message.SubString(message.Pos('%') + 1, message.Length() - message.Pos('%')));
    }
}


void __fastcall TFormMain::ServerSocketClientDisconnect(TObject* Sender,
	TCustomWinSocket* Socket)
{
	if (ServerSocket->Socket->ActiveConnections != 0)
	{
		for (int i = 0; i < mass; i++)
		{
			m[i] = "";
		}
		TestNames();

		Timer1->Enabled = true;

	}
}