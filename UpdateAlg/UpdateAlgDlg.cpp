
// UpdateAlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpdateAlg.h"
#include "UpdateAlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateAlgDlg 对话框

CUpdateAlgDlg::CUpdateAlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpdateAlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateAlgDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_DISABLE, m_treeDisFile);
    DDX_Control(pDX, IDC_TREE_ENABLE, m_treeEnFile);
    DDX_Control(pDX, IDC_EDIT1, m_editLog);
}

BEGIN_MESSAGE_MAP(CUpdateAlgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_FIND, &CUpdateAlgDlg::OnBnClickedButtonFind)
    ON_BN_CLICKED(IDC_BUTTON_LEFT, &CUpdateAlgDlg::OnBnClickedButtonLeft)
    ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CUpdateAlgDlg::OnBnClickedButtonRight)
    ON_BN_CLICKED(IDC_BUTTON_DO, &CUpdateAlgDlg::OnBnClickedButtonDo)
END_MESSAGE_MAP()


// CUpdateAlgDlg 消息处理程序

BOOL CUpdateAlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码 
    HICON  hIcon[4]; 
    TCHAR  sCurPath[MAX_PATH_LENGTH];

    GetCurrentDirectory(MAX_PATH_LENGTH, sCurPath);
    m_sCurPath = sCurPath;
    m_sCurPath += "\\alg";
    
    // 加载三个图标，并将它们的句柄保存到数组   
    hIcon[0] = theApp.LoadIcon(IDI_FOLDER);   
    hIcon[1] = theApp.LoadIcon(IDI_CFILE);   
    hIcon[2] = theApp.LoadIcon(IDI_CPPFILE); 
    hIcon[3] = theApp.LoadIcon(IDI_HFILE);

    // 创建图像序列CImageList对象   
    m_imageList.Create(16, 16, ILC_COLOR32, 4, 4);
    m_imageList.SetBkColor(m_treeEnFile.GetBkColor()&0xFFFFFF);
    // 将三个图标添加到图像序列   
    for (int i=0; i<4; i++)   
    {   
        m_imageList.Add(hIcon[i]);   
    }   
    
    // 为树形控件设置图像序列   
    m_treeDisFile.SetImageList(&m_imageList, TVSIL_NORMAL); 
    m_treeEnFile.SetImageList(&m_imageList, TVSIL_NORMAL); 

    m_hItemDisSrc = m_treeDisFile.InsertItem("源文件", 0, 0, TVI_ROOT);
    m_hItemDisSrh = m_treeDisFile.InsertItem("头文件", 0, 0, TVI_ROOT);
    m_hItemEnSrc = m_treeEnFile.InsertItem("src", 0, 0, TVI_ROOT);
    m_hItemEnSrh = m_treeEnFile.InsertItem("srh", 0, 0, TVI_ROOT);
//     hRoot = m_treeDisFile.InsertItem(_T("鸡啄米"), 0, 0);   
//     // 在根节点下插入子节点   
//     hCataItem = m_treeDisFile.InsertItem(_T("IT互联网"), 1, 1, hRoot, TVI_LAST);   
//     // 为“IT互联网”节点添加附加的编号数据，在鼠标划过该节点时显示   
//     m_treeDisFile.SetItemData(hCataItem, 1);   
//     // 在“IT互联网”节点下插入子节点   
//     hArtItem = m_treeDisFile.InsertItem(_T("百度文章1"), 2, 2, hCataItem, TVI_LAST);   
//     // 为“百度文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
//     m_treeDisFile.SetItemData(hArtItem, 2);   
//     // 在“IT互联网”节点下插入另一子节点   
//     hArtItem = m_treeDisFile.InsertItem(_T("谷歌文章2"), 2, 2, hCataItem, TVI_LAST); 
//      
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpdateAlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpdateAlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CUpdateAlgDlg::PrintLog(const char* fmt,...)
{
    CString strLog;
    va_list argp;
    va_start(argp,fmt);
    strLog.FormatV(fmt,argp);
    va_end(argp);
    if(m_editLog.GetLineCount() > MAX_LOG_LINE)
    {
        int size = 0;
        for(int i = 0; i < MAX_LOG_LINE/2; i++)
        {
            size += m_editLog.LineLength(m_editLog.LineIndex(i));
        }
        m_editLog.SetSel(0,size+2);
        m_editLog.Clear();
    }
    m_editLog.SetSel(-1);
    m_editLog.ReplaceSel(strLog);
    m_editLog.LineScroll(m_editLog.GetLineCount(),0);
    UpdateData(FALSE);
}

void CUpdateAlgDlg::Recurse(CString pstr, CString type, CString& strText)
{
    CFileFind finder;
    // build a string with wildcards
    CString strWildcard = pstr;
    strWildcard += "\\" + type;
    // start working for files
    BOOL bWorking = finder.FindFile(strWildcard);

    while(bWorking)
    {
        bWorking = finder.FindNextFile();

        // skip . and .. files; otherwise, we'd
        // recur infinitely!

        if(finder.IsDots())
            continue;

        // if it's a directory, recursively search it
        CString str = finder.GetFilePath();
        if(finder.IsDirectory())
        {
            Recurse(str, type, strText);
        }
        else
        {
            int pos = m_sCurPath.GetLength();
            str = str.Mid(pos+1);
            strText += str + _T("\r\n");
            if(_tcsstr(str, ".c") || _tcsstr(str, ".cpp")){
                m_listEnableSrc.AddTail(str);
                PrintLog("src==%s\r\n",str);
            }
            else if(_tcsstr(str, ".h")){
                m_listEnableSrh.AddTail(str);
                PrintLog("srh==%s\r\n",str);
            }
        }
    }
    finder.Close();
}
void CUpdateAlgDlg::RemoveInvalidItem()
{
    HTREEITEM hItem;
    if(m_treeDisFile.ItemHasChildren(m_hItemDisSrc))//遍历disable src
    {
        hItem = m_treeDisFile.GetChildItem(m_hItemDisSrc);
        while(hItem != NULL)
        {
            /* 当前文件存在 */
            if(m_listEnableSrc.Find(m_treeDisFile.GetItemText(hItem)))
                ;
            else //当前文件不存在，从tree中移除
                m_treeDisFile.DeleteItem(hItem);
            hItem = m_treeDisFile.GetNextSiblingItem(hItem);
        }
    }
    if(m_treeEnFile.ItemHasChildren(m_hItemEnSrc))//遍历disable src
    {
        hItem = m_treeEnFile.GetChildItem(m_hItemEnSrc);
        while(hItem != NULL)
        {
            /* 当前文件存在 */
            if(m_listEnableSrc.Find(m_treeEnFile.GetItemText(hItem)))
                ;
            else //当前文件不存在，从tree中移除
                m_treeEnFile.DeleteItem(hItem);
            hItem = m_treeEnFile.GetNextSiblingItem(hItem);
        }
    }
    if(m_treeDisFile.ItemHasChildren(m_hItemDisSrh))//遍历disable src
    {
        hItem = m_treeDisFile.GetChildItem(m_hItemDisSrh);
        while(hItem != NULL)
        {
            /* 当前文件存在 */
            if(m_listEnableSrh.Find(m_treeDisFile.GetItemText(hItem)))
                ;
            else //当前文件不存在，从tree中移除
                m_treeDisFile.DeleteItem(hItem);
            hItem = m_treeDisFile.GetNextSiblingItem(hItem);
        }
    }
    if(m_treeEnFile.ItemHasChildren(m_hItemEnSrh))//遍历disable src
    {
        hItem = m_treeEnFile.GetChildItem(m_hItemEnSrh);
        while(hItem != NULL)
        {
            /* 当前文件存在 */
            if(m_listEnableSrh.Find(m_treeEnFile.GetItemText(hItem)))
                ;
            else //当前文件不存在，从tree中移除
                m_treeEnFile.DeleteItem(hItem);
            hItem = m_treeEnFile.GetNextSiblingItem(hItem);
        }
    }


}
BOOL CUpdateAlgDlg::FindItem(HTREEITEM item, CString strtext, int type)
{
    HTREEITEM hItem;
    HTREEITEM htreeItem;
    CTreeCtrl *treeCtrl;
    switch(type)
    {
    case FIND_DISABLE_SRC:
        htreeItem = m_hItemDisSrc;
        treeCtrl = &m_treeDisFile;
        break;
    case FIND_DISABLE_SRH:
        htreeItem = m_hItemDisSrh;
        treeCtrl = &m_treeDisFile;
        break;
    case FIND_ENABLE_SRC:
        htreeItem = m_hItemEnSrc;
        treeCtrl = &m_treeEnFile;
        break;
    case FIND_ENABLE_SRH:
        htreeItem = m_hItemEnSrh;
        treeCtrl = &m_treeEnFile;
        break;
    default:
        return FALSE;
    }
    if(treeCtrl->ItemHasChildren(htreeItem))//遍历disable src
    {
        hItem = treeCtrl->GetChildItem(htreeItem);
        while(hItem != NULL)
        {
            /* 当前文件存在 */
            if(treeCtrl->GetItemText(hItem) == strtext)
                return TRUE;
            hItem = treeCtrl->GetNextSiblingItem(hItem);
        }
    }
    return FALSE;
}
CString CUpdateAlgDlg::ExecuteCmd(CString cmd)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE hRead,hWrite;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    if (!CreatePipe(&hRead,&hWrite,&sa,0))
    {
        MessageBox("Error on CreatePipe()!");
        return NULL;
    }
    STARTUPINFO si={sizeof(si)};
    PROCESS_INFORMATION pi;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    CString tmp;
    tmp.Format("cmd /C %s",cmd);
    LPTSTR cmdline = tmp.GetBuffer();
    if (!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))
    {
        MessageBox("Error on CreateProcess()!");
        return NULL;
    }
    CloseHandle(hWrite);

    char buffer[4096];
    memset(buffer,0,4096);
    CString output;
    DWORD byteRead;
    while(true)
    {
        if (ReadFile(hRead,buffer,4095,&byteRead,NULL) == NULL)
        {
            break;
        }
        output += buffer;
    }
    return output;
}
void CUpdateAlgDlg::OnBnClickedButtonFind()
{
    // TODO: 在此添加控件通知处理程序代码
    CString strText(_T("find:\r\n"));
    HTREEITEM hItem;
    m_listEnableSrc.RemoveAll();
    m_listEnableSrh.RemoveAll();
    Recurse(m_sCurPath, "*.*", strText);
    //    PrintLog("%s",strText);
//    m_treeEnFile.DeleteAllItems();
    RemoveInvalidItem();

    POSITION pos = m_listEnableSrc.GetHeadPosition();
    for(; pos!=NULL; m_listEnableSrc.GetNext(pos))
    {
        strText = m_listEnableSrc.GetAt(pos);
        if(!FindItem(NULL, strText, FIND_DISABLE_SRC) && !FindItem(NULL, strText, FIND_ENABLE_SRC))
            m_treeEnFile.InsertItem(strText, 1, 1, m_hItemEnSrc, TVI_LAST);
    }


    pos = m_listEnableSrh.GetHeadPosition();
    for(; pos!=NULL; m_listEnableSrh.GetNext(pos))
    {
        strText = m_listEnableSrh.GetAt(pos);
        if(!FindItem(NULL, strText, FIND_DISABLE_SRH) && !FindItem(NULL, strText, FIND_ENABLE_SRH))
            m_treeEnFile.InsertItem(strText, 3, 3, m_hItemEnSrh, TVI_LAST);
    }
    m_treeDisFile.Expand(m_hItemDisSrc, TVE_EXPAND);
    m_treeDisFile.Expand(m_hItemDisSrh, TVE_EXPAND);
    m_treeEnFile.Expand(m_hItemEnSrc, TVE_EXPAND);
    m_treeEnFile.Expand(m_hItemEnSrh, TVE_EXPAND);
}

void CUpdateAlgDlg::OnBnClickedButtonLeft()
{
    // TODO: 在此添加控件通知处理程序代码
    HTREEITEM hItem = m_treeEnFile.GetSelectedItem();
    if(hItem == m_hItemEnSrc || hItem == m_hItemEnSrh)
        return ;
    HTREEITEM hParItem = m_treeEnFile.GetParentItem(hItem);
    if(hParItem == m_hItemEnSrc)
    {
        m_treeDisFile.InsertItem(m_treeEnFile.GetItemText(hItem),1,1,m_hItemDisSrc,TVI_LAST);
        m_treeEnFile.DeleteItem(hItem);
        m_treeDisFile.Expand(m_hItemDisSrc, TVE_EXPAND);
    }
    if(hParItem == m_hItemEnSrh)
    {
        m_treeDisFile.InsertItem(m_treeEnFile.GetItemText(hItem),3,3,m_hItemDisSrh,TVI_LAST);
        m_treeEnFile.DeleteItem(hItem);
        m_treeDisFile.Expand(m_hItemDisSrh, TVE_EXPAND);
    }

}

void CUpdateAlgDlg::OnBnClickedButtonRight()
{
    // TODO: 在此添加控件通知处理程序代码
    HTREEITEM hItem = m_treeDisFile.GetSelectedItem();
    if(hItem == m_hItemDisSrc || hItem == m_hItemDisSrh)
        return ;
    HTREEITEM hParItem = m_treeDisFile.GetParentItem(hItem);
    if(hParItem == m_hItemDisSrc)
    {
        m_treeEnFile.InsertItem(m_treeDisFile.GetItemText(hItem),1,1,m_hItemEnSrc,TVI_LAST);
        m_treeDisFile.DeleteItem(hItem);
    }
    if(hParItem == m_hItemDisSrh)
    {
        m_treeEnFile.InsertItem(m_treeDisFile.GetItemText(hItem),3,3,m_hItemEnSrh,TVI_LAST);
        m_treeDisFile.DeleteItem(hItem);
    }
}

const char fileHead[][128] = {
    "CC = cl.exe",
    "LINK = link.exe",
//     "CFLAG = /c /I $(INCLUDE)",
//     "OFLAG = /libpath:$(LIB)",
    "OUTDIR = .\\out",
    "TARG = $(OUTDIR)\\libalg.dll",
    "",
    "all:clean $(OUTDIR) $(TARG)",
    "",
    "$(OUTDIR):",
    "    if not exist \"$(OUTDIR)\" mkdir $(OUTDIR)",
    ".c.obj::",
    "    $(CC) -c /Fo\"$(OUTDIR)\\\" /Fd\"$(OUTDIR)\\\" $<"
};
const char CCLine[] = "    $(CC) -c /Fo\"$(OUTDIR)\\\" /Fd\"$(OUTDIR)\\\" $<\r\n";
const char LinkTarg[] = "$(TARG): ";
const char LinkLine[] = "    $(LINK) /dll /def:libalg.def /out:$(TARG) $(OUTDIR)\*.obj\r\n";
const char fileTail[][128] = {
    "clean:",
    "    del $(OUTDIR)\\*.obj",
    "    del $(OUTDIR)\\*.lib",
    "    del $(OUTDIR)\\*.exp",
    "",
    "all:$(OUTDIR) $(TARG)",
    "",
    "$(OUTDIR):",
    "    if not exist \"$(OUTDIR)\" mkdir $(OUTDIR)"
};

CString CUpdateAlgDlg::CCLineProcess()
{
    CString strText;
    CString strRes;
    int     npos;
    CList<CString> sSrcFolder;
    HTREEITEM hItem;
    if(m_treeEnFile.ItemHasChildren(m_hItemEnSrc))//遍历enable src
    {
        hItem = m_treeEnFile.GetChildItem(m_hItemEnSrc);
        while(hItem != NULL)
        {
            /* 获取Item 文本 */
            strText = m_treeDisFile.GetItemText(hItem);
            if((npos = strText.ReverseFind('\\')) >= 0)
            {
                strText = strText.Left(npos);
                if(sSrcFolder.Find(strText) == NULL)
                {
                    sSrcFolder.AddTail(strText);
                    PrintLog(".\\%s",strText);
                }
            }
            hItem = m_treeEnFile.GetNextSiblingItem(hItem);
        }
    }

    POSITION pos = sSrcFolder.GetHeadPosition();
    for(; pos!=NULL; sSrcFolder.GetNext(pos))
    {
        strText = m_listEnableSrc.GetAt(pos);
        strText.Format("{.\\%s}.c.obj::\r\n",strText);
        strRes += strText;
        strText.Format("%s",CCLine);
        strRes += strText;
    }
    return strRes;
}
void CUpdateAlgDlg::OnBnClickedButtonDo()
{
    // TODO: 在此添加控件通知处理程序代码
    CString res;
    CFile   *pMakeFile;
    int     i = 0;
    SetCurrentDirectory(m_sCurPath);
    pMakeFile = new CFile(".\\makefile", CFile::modeCreate | CFile::modeWrite);

    for(i = 0; i < sizeof(fileHead)/sizeof(fileHead[0]); i++)
    {
        pMakeFile->Write(fileHead[i], strlen(fileHead[i]));
        pMakeFile->Write("\r\n", 2);
    }
    res = CCLineProcess();
    pMakeFile->Write(res, res.GetLength());
//    res = ExecuteCmd("dir");
    
    delete pMakeFile;
}
