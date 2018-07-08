//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit5.cpp", Form5);
USEFORM("Unit6.cpp", Form6);
USEFORM("Unit7.cpp", Form7);
USEFORM("Unit8.cpp", Form8);
USEFORM("Unit9.cpp", Form9);
USEFORM("Unit1.cpp", Form1);
USEFORM("DataCtrl.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("Unit10.cpp", Form10);
USEFORM("Unit11.cpp", Form11);
USEFORM("Main.cpp", Form12);
USEFORM("Unit13.cpp", Form13);
USEFORM("Unit14.cpp", Form14);
USEFORM("Unit15.cpp", Form15);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit16.cpp", Form16);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "多媒体综合显示系统控制台";
                 //Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TDataModule1), &DataModule1);
                 Application->CreateForm(__classid(TForm1), &Form1);
                 
                 Application->CreateForm(__classid(TForm3), &Form3);
                 Application->CreateForm(__classid(TForm4), &Form4);
                 Application->CreateForm(__classid(TForm5), &Form5);
                 Application->CreateForm(__classid(TForm6), &Form6);
                 Application->CreateForm(__classid(TForm8), &Form8);
                 Application->CreateForm(__classid(TForm9), &Form9);
                 Application->CreateForm(__classid(TForm10), &Form10);
                 Application->CreateForm(__classid(TForm11), &Form11);
                 Application->CreateForm(__classid(TForm12), &Form12);
                 Application->CreateForm(__classid(TForm13), &Form13);
                 Application->CreateForm(__classid(TForm14), &Form14);
                 Application->CreateForm(__classid(TForm15), &Form15);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TForm16), &Form16);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
