//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm9 : public TForm
{
__published:	// IDE-managed Components
        TListView *ListView1;
        TButton *Button1;
        TButton *Button2;
        TImageList *ImageList1;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int     SelType;//ѡ���ý�����ͣ�1-��Ƶ��2��ѭ��ͼƬ��3�������ı�
        BOOL    SelFlag;//ѡ���־���Ƿ���ѡ�����ͣ�1-��ѡ��0-δѡ��
        __fastcall TForm9(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm9 *Form9;
//---------------------------------------------------------------------------
#endif
