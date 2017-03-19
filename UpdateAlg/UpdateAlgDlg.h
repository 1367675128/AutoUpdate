
// UpdateAlgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define MAX_LOG_LINE 500

#define MAX_PATH_LENGTH 512

enum{
    FIND_DISABLE_SRC,
    FIND_DISABLE_SRH,
    FIND_ENABLE_SRC,
    FIND_ENABLE_SRH,
};
// CUpdateAlgDlg �Ի���
class CUpdateAlgDlg : public CDialogEx
{
// ����
public:
	CUpdateAlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPDATEALG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CImageList m_imageList;
    CTreeCtrl m_treeDisFile;
    CTreeCtrl m_treeEnFile;
    HTREEITEM m_hItemEnSrc;
    HTREEITEM m_hItemEnSrh;
    HTREEITEM m_hItemDisSrc;
    HTREEITEM m_hItemDisSrh;
    CEdit m_editLog;
    CString m_sCurPath;
    CList<CString> m_listDisableSrc;
    CList<CString> m_listDisableSrh;
    CList<CString> m_listEnableSrc;
    CList<CString> m_listEnableSrh;
    afx_msg void OnBnClickedButtonFind();
    void PrintLog(const char* fmt,...);
    void Recurse(CString pstr, CString type, CString& strText);
    void RemoveInvalidItem();
    CString ExecuteCmd(CString str);
    CString CCLineProcess(CString &strObj);
    BOOL FindItem(HTREEITEM item, CString strtext, int type);
    afx_msg void OnBnClickedButtonLeft();
    afx_msg void OnBnClickedButtonRight();
    afx_msg void OnBnClickedButtonDo();
};
