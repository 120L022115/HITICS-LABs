#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include<strsafe.h>
//#include"sysmets.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
//������
// �ĸ�������
//hInstance : ����ǰʵ���ľ��(handle to current instance)���Ժ���ʱ������GetModuleHandle(0)�����
//hPrevInstance : ǰһ��ʵ���ľ��(handle to previous instance)����Win32�У�ÿһ�����̶���һ��������4G��ַ�ռ䣬��0��2G���ڽ���˽�У�������������˵�ǲ��ɼ��ġ����ԣ���Win32�У�hPrevInstance����ΪNULL��
//szCmdLine : ָ���� / 0��β�������У�������EXE������ļ���(pointer to command line)���Ժ���ʱ������GetCommandLine()����ȡ�����������С�
//iCmdShow : ָ��Ӧ����ʲô��ʽ��ʾ������(show state of window)��

{
    static TCHAR szAppName[] = TEXT("MyWindows");
    HWND hwnd;//���
    MSG msg;//��Ϣ
    WNDCLASS wndclass;//���崰����ṹ
    HBRUSH hCulorBrush = CreateSolidBrush(RGB(200, 200, 200));//�趨������ɫ

    //�ṹ��Ա��
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //��������
    wndclass.lpfnWndProc = WndProc;  //���ڹ��̣������ǻص�������
    wndclass.cbClsExtra = 0;//Ԥ���Ķ���ռ䣬һ��Ϊ0
    wndclass.cbWndExtra = 0;//Ԥ���Ķ���ռ䣬һ��Ϊ0
    wndclass.hInstance = hInstance;//Ӧ�ó����ʵ�����
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Ϊ���л��ڸô�����Ĵ����趨һ��ͼ��
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//Ϊ���л��ڸô�����Ĵ����趨һ�����ָ��
    //wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//ָ�����ڱ���ɫ
    wndclass.hbrBackground = hCulorBrush;//ָ�����ڱ���ɫ
    wndclass.lpszMenuName = NULL; //ָ�����ڲ˵�
    wndclass.lpszClassName = szAppName; //ָ����������

    //ע�ᴰ����
    if (!RegisterClass(&wndclass))
        /*  RegisterClass��ע����������CreateWindow������CreateWindowEx������ʹ�õĴ����ࡣ
          ����ΪlpWndClass��ָ��һ��WNDCLASS�ṹ��ָ��
          ����ֵ��ATOM�ĺ궨��
          typedef WORD ATOM;
          typedef unsigned short WORD;
          ����RegisterClassEx:����lpwcxָ��һ��WNDCLASSEX�ṹ��ָ����������ɹ�����������������͵ı�ʶ�ţ�
          �������ʧ�ܣ�����ֵΪ0�������ø��������Ϣ�������GetLastError������*/
    {
        MessageBox(NULL, TEXT("���������Ҫ��Windowsϵͳִ�У�"), szAppName, MB_ICONERROR);
        return 0;
    }
    //ʵ������������
    hwnd = CreateWindow(szAppName,// ����������
        TEXT("������ѧC����Windows�������"),// ���ڱ���
        WS_OVERLAPPEDWINDOW|WS_VSCROLL,// ���ڷ�񣬻�ƴ��ڸ�ʽ
        CW_USEDEFAULT,// ��ʼ x ����
        CW_USEDEFAULT, // ��ʼ y ����
        CW_USEDEFAULT,// ��ʼ x ����ߴ�
        CW_USEDEFAULT,// ��ʼ y ����ߴ�
        NULL,// �����ھ��
        NULL,// ���ڲ˵����
        hInstance,// ����ʵ�����
        NULL);// ��������

    /*_In_˵���ò���������ģ�_opt_˵���ò����ǿ�ѡ����
        �����ɹ����ش��ھ�������򷵻�NULL*/

        //��ʾ����
    ShowWindow(hwnd, iCmdShow);
    /* ��һ�ε���ʱӦʹ��WinMain�Ĳ���nCmdShow��Ϊ����
         �������֮ǰ�ɼ����򷵻ط�0���򷵻�0*/

         //���´���
    UpdateWindow(hwnd);
    /* �ƹ���Ϣ����ֱ���򴰿ڹ��̷���WM_PAINT��Ϣ
         �������óɹ����ط�0*/

         //��Ϣѭ��
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    /*���ã��ӵ�ǰ�̵߳���Ϣ������ȡ��һ����Ϣ������MSG�ṹ�У����ܻ�������̵߳���Ϣ
        ����Ϣ����Ϊ�գ�������һֱ�ȴ�������Ϣ�������з���ֵ
        ����ֵ��
        �������ִ����򷵻� - 1��
        ���WM_QUIT��Ϣ����0
        ���򷵻ط�0*/

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
/*�ص�����
//������
hwnd : ���ھ��
message : ��ϢID
wParam��lParam����Ϣ����*/
    //int i;
    //size_t j;
    HDC hdc;;//�����豸�������  
    static TCHAR  szBuffer[128];
    //TEXTMETRIC tm;
   // SCROLLINFO si;
    PAINTSTRUCT ps;
    RECT rect;
    size_t iStrLength;
    static int cxChar, cyChar, yVscrollPos, cxClient, cyClient, yPage,cxCaps, FirstLine, LastLine;
    switch (message)
    {

        case WM_SIZE://�����С�ı�
            hdc = GetDC(hWnd);
            //GetClientRect(hwnd, &rect);
            cxClient = LOWORD(lParam);//��ǰx����
            cyClient = HIWORD(lParam);//��ǰy����
            StringCchPrintf(szBuffer, 128, TEXT("��ǰ�ͻ����ķֱ���:%d * %d px"), cxClient, cyClient);
            StringCchLength(szBuffer, 128, &iStrLength);
            SetTextAlign(hdc, TA_CENTER | TA_TOP);
            TextOut(hdc, cxClient / 2, 0, szBuffer, iStrLength);
            ReleaseDC(hWnd, hdc);
            return 0;

        case WM_PAINT://���ڻ滭����
        {
            int x,xLast;
            HDC hdc = BeginPaint(hWnd, &ps);//����Ϊָ�����ڽ��л滭��׼�������ý��ͻ滭�йص���Ϣ��䵽һ�� PAINTSTRUCT �ṹ�С�
            GetClientRect(hWnd, &rect);//��ȡ�ͻ�����Ϣ. �������ڻ�ȡ���ڿͻ��������꣬�ͻ�������ָ���ͻ��������ϽǺ����½ǡ�
            xLast = rect.right;//��ÿͻ������Ҳ�����
            for (x = 0; x < xLast; x++)//ѭ��x�������
            {
                SetPixel(hdc, x, 100, RGB(255, 0, 0));//�ڿͻ����ϻ���
            }
            EndPaint(hWnd, &ps);
            return 0;
        } 
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    return 0;
}

