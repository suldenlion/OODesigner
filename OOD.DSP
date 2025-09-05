# Microsoft Developer Studio Project File - Name="OOD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OOD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OOD.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OOD.MAK" CFG="OOD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OOD - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OOD - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OOD - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "OOD - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OOD - Win32 Release"
# Name "OOD - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActivationBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivationBarList.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivationBarPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\Activity.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivityMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ActivityText.cpp
# End Source File
# Begin Source File

SOURCE=.\Actor.cpp
# End Source File
# Begin Source File

SOURCE=.\ActorNameText.cpp
# End Source File
# Begin Source File

SOURCE=.\Aggregation.cpp
# End Source File
# Begin Source File

SOURCE=.\AggregationPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\Anchor.cpp
# End Source File
# Begin Source File

SOURCE=.\AnchorList.cpp
# End Source File
# Begin Source File

SOURCE=.\AnytionInfoTuple.cpp
# End Source File
# Begin Source File

SOURCE=.\ArgumentInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ArgumentList.cpp
# End Source File
# Begin Source File

SOURCE=.\Association.cpp
# End Source File
# Begin Source File

SOURCE=.\AssociationPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseClassInitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BeginActivity.cpp
# End Source File
# Begin Source File

SOURCE=.\Box.cpp
# End Source File
# Begin Source File

SOURCE=.\Bucket.cpp
# End Source File
# Begin Source File

SOURCE=.\CActivityFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CActivityView.cpp
# End Source File
# Begin Source File

SOURCE=.\CaptureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CChooseDirDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CClassDeleteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CClassFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CClassMigrationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CClassView.cpp
# End Source File
# Begin Source File

SOURCE=.\CCollaborationFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CCollaborationView.cpp
# End Source File
# Begin Source File

SOURCE=.\CDeploymentFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CDeploymentView.cpp
# End Source File
# Begin Source File

SOURCE=.\CInPlaceFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Circle.cpp
# End Source File
# Begin Source File

SOURCE=.\CITList.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassContent.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassDocumentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassFigureLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassMemberListView.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassOthersOption.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTemplatePopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassText.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTextLine.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\CMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CNewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CNewWSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CObjectFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CObjectView.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\CollaborationMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CollaborationMultiObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CollaborationObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CollaborationObjectMessageText.cpp
# End Source File
# Begin Source File

SOURCE=.\CollaborationObjectPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CommentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Communication.cpp
# End Source File
# Begin Source File

SOURCE=.\ComponentTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\ComponentText.cpp
# End Source File
# Begin Source File

SOURCE=.\Connection.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectionInfoTuple.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectionList.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectionPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectionText.cpp
# End Source File
# Begin Source File

SOURCE=.\COODClassDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\COODCntrlItem.cpp
# End Source File
# Begin Source File

SOURCE=.\COODCntrlItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\COODCommonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\COODCommonFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\COODCommonView.cpp
# End Source File
# Begin Source File

SOURCE=.\COODDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\COODSrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\COODView.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPClassPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPCommonCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPMethodPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPVarPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsCodeGen.cpp
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsMacros.cpp
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsReverse.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableDockContext.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableDockState.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableEditDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableEditViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableMiniDockFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizableTreeBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CResizeEditViewBarDocTemp.cpp
# End Source File
# Begin Source File

SOURCE=.\CSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSequenceFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CSequenceView.cpp
# End Source File
# Begin Source File

SOURCE=.\CSharpClassPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CSharpCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\CSharpMethodPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CSharpVarPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\CSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=.\CStateFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CStateView.cpp
# End Source File
# Begin Source File

SOURCE=.\CTextDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CTextFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CUseCaseFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CUseCaseView.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CWndSpaceElt.cpp
# End Source File
# Begin Source File

SOURCE=.\DataMembersOption.cpp
# End Source File
# Begin Source File

SOURCE=.\Dependency.cpp
# End Source File
# Begin Source File

SOURCE=.\DependencyPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\DeploymentMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\Diamond.cpp
# End Source File
# Begin Source File

SOURCE=.\EditableFigure.cpp
# End Source File
# Begin Source File

SOURCE=.\EditPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\EndActivity.cpp
# End Source File
# Begin Source File

SOURCE=.\Etc.cpp
# End Source File
# Begin Source File

SOURCE=.\EventText.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcludeRect.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcludeRectList.cpp
# End Source File
# Begin Source File

SOURCE=.\Figure.cpp
# End Source File
# Begin Source File

SOURCE=.\FigureLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\FigureList.cpp
# End Source File
# Begin Source File

SOURCE=.\FinalState.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedNamesTable.cpp
# End Source File
# Begin Source File

SOURCE=.\FontInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Generalization.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralizationPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\HardwareNode.cpp
# End Source File
# Begin Source File

SOURCE=.\HWConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\HWConnectionText.cpp
# End Source File
# Begin Source File

SOURCE=.\InitialState.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfacePort.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfacePortList.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfacePortPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfacePortText.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaClassPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaMethodPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaVarPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\LineList.cpp
# End Source File
# Begin Source File

SOURCE=.\LineNode.cpp
# End Source File
# Begin Source File

SOURCE=.\LineNodeList.cpp
# End Source File
# Begin Source File

SOURCE=.\LinePopup.cpp
# End Source File
# Begin Source File

SOURCE=.\Lines.cpp
# End Source File
# Begin Source File

SOURCE=.\List.cpp
# End Source File
# Begin Source File

SOURCE=.\ListNode.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberFunctionsOption.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberOptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MemberPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageFlow.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageFlowPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageText.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageTextPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\MethodBodyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeFigure.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeFigureList.cpp
# End Source File
# Begin Source File

SOURCE=.\Note.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteBoundary.cpp
# End Source File
# Begin Source File

SOURCE=.\NoteText.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPositionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectText.cpp
# End Source File
# Begin Source File

SOURCE=.\OneLineText.cpp
# End Source File
# Begin Source File

SOURCE=.\OOD.cpp
# End Source File
# Begin Source File

SOURCE=.\OOD.rc
# End Source File
# Begin Source File

SOURCE=.\PackageCommentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PackageLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\PackagePopup.cpp
# End Source File
# Begin Source File

SOURCE=.\PackagePropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PackagePropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\PackageTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\PackageText.cpp
# End Source File
# Begin Source File

SOURCE=.\Popup.cpp
# End Source File
# Begin Source File

SOURCE=.\PropCommonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QualificationText.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RelationshipInfoTuple.cpp
# End Source File
# Begin Source File

SOURCE=.\RelationshipInfoTupleList.cpp
# End Source File
# Begin Source File

SOURCE=.\RelationTraverseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RelationTraverseFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizeGlobalData.cpp
# End Source File
# Begin Source File

SOURCE=.\RoundBoxA.cpp
# End Source File
# Begin Source File

SOURCE=.\RoundBoxB.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenCaptureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceAsyncMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceLanePopup.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceMessageText.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceObjectPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceReturnMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceSelfDelegation.cpp
# End Source File
# Begin Source File

SOURCE=.\SequenceSyncMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveryText.cpp
# End Source File
# Begin Source File

SOURCE=.\SlaveryTextList.cpp
# End Source File
# Begin Source File

SOURCE=.\State.cpp
# End Source File
# Begin Source File

SOURCE=.\StateMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\StatePopup.cpp
# End Source File
# Begin Source File

SOURCE=.\StateText.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticConnectionText.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SyncConditionText.cpp
# End Source File
# Begin Source File

SOURCE=.\SynchronizationBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SynchronizationPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemBoundary.cpp
# End Source File
# Begin Source File

SOURCE=.\TabDlgWithName.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateClassTag.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateClassTagText.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\TextContent.cpp
# End Source File
# Begin Source File

SOURCE=.\TextLine.cpp
# End Source File
# Begin Source File

SOURCE=.\TipBoard.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Transition.cpp
# End Source File
# Begin Source File

SOURCE=.\Triangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\TriggerText.cpp
# End Source File
# Begin Source File

SOURCE=.\TupleText.cpp
# End Source File
# Begin Source File

SOURCE=.\TwoPointFigure.cpp
# End Source File
# Begin Source File

SOURCE=.\UnsignedLong.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCase.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCaseExtendsLink.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCaseLink.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCaseMainPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCaseText.cpp
# End Source File
# Begin Source File

SOURCE=.\UseCaseUsesLink.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPClassPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPClassPropMaps.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPCodeGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPMapEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPMethodPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\VCPPVarPropGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\VTerm.cpp
# End Source File
# Begin Source File

SOURCE=.\WidePackage.cpp
# End Source File
# Begin Source File

SOURCE=.\WideState.cpp
# End Source File
# Begin Source File

SOURCE=.\WideStateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\YCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomComboBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActivationBar.h
# End Source File
# Begin Source File

SOURCE=.\ActivationBarList.h
# End Source File
# Begin Source File

SOURCE=.\ActivationBarPopup.h
# End Source File
# Begin Source File

SOURCE=.\Activity.h
# End Source File
# Begin Source File

SOURCE=.\ActivityMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\ActivityText.h
# End Source File
# Begin Source File

SOURCE=.\Actor.h
# End Source File
# Begin Source File

SOURCE=.\ActorNameText.h
# End Source File
# Begin Source File

SOURCE=.\AfxDeleteExceptionMacro.h
# End Source File
# Begin Source File

SOURCE=.\Aggregation.h
# End Source File
# Begin Source File

SOURCE=.\AggregationPopup.h
# End Source File
# Begin Source File

SOURCE=.\Anchor.h
# End Source File
# Begin Source File

SOURCE=.\AnchorList.h
# End Source File
# Begin Source File

SOURCE=.\AnytionInfoTuple.h
# End Source File
# Begin Source File

SOURCE=.\ArgumentInfo.h
# End Source File
# Begin Source File

SOURCE=.\ArgumentList.h
# End Source File
# Begin Source File

SOURCE=.\Association.h
# End Source File
# Begin Source File

SOURCE=.\AssociationPopup.h
# End Source File
# Begin Source File

SOURCE=.\BaseClassInitDlg.h
# End Source File
# Begin Source File

SOURCE=.\BeginActivity.h
# End Source File
# Begin Source File

SOURCE=.\Box.h
# End Source File
# Begin Source File

SOURCE=.\Bucket.h
# End Source File
# Begin Source File

SOURCE=.\builtInClasses.h
# End Source File
# Begin Source File

SOURCE=.\CActivityFrm.h
# End Source File
# Begin Source File

SOURCE=.\CActivityView.h
# End Source File
# Begin Source File

SOURCE=.\CaptureDlg.h
# End Source File
# Begin Source File

SOURCE=.\CChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CChooseDirDlg.h
# End Source File
# Begin Source File

SOURCE=.\CClassDeleteDlg.h
# End Source File
# Begin Source File

SOURCE=.\CClassFrm.h
# End Source File
# Begin Source File

SOURCE=.\CClassMigrationDlg.h
# End Source File
# Begin Source File

SOURCE=.\CClassView.h
# End Source File
# Begin Source File

SOURCE=.\CCollaborationFrm.h
# End Source File
# Begin Source File

SOURCE=.\CCollaborationView.h
# End Source File
# Begin Source File

SOURCE=.\CDeploymentFrm.h
# End Source File
# Begin Source File

SOURCE=.\CDeploymentView.h
# End Source File
# Begin Source File

SOURCE=.\CInPlaceFrame.h
# End Source File
# Begin Source File

SOURCE=.\Circle.h
# End Source File
# Begin Source File

SOURCE=.\CITList.h
# End Source File
# Begin Source File

SOURCE=.\ClassContent.h
# End Source File
# Begin Source File

SOURCE=.\ClassDocumentDlg.h
# End Source File
# Begin Source File

SOURCE=.\Classes.h
# End Source File
# Begin Source File

SOURCE=.\ClassFigureLibrary.h
# End Source File
# Begin Source File

SOURCE=.\ClassLibrary.h
# End Source File
# Begin Source File

SOURCE=.\ClassMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\ClassMemberListView.h
# End Source File
# Begin Source File

SOURCE=.\ClassOthersOption.h
# End Source File
# Begin Source File

SOURCE=.\ClassPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClassTemplate.h
# End Source File
# Begin Source File

SOURCE=.\ClassTemplatePopup.h
# End Source File
# Begin Source File

SOURCE=.\ClassText.h
# End Source File
# Begin Source File

SOURCE=.\ClassTextLine.h
# End Source File
# Begin Source File

SOURCE=.\ClassTreeView.h
# End Source File
# Begin Source File

SOURCE=.\CMainFrame.h
# End Source File
# Begin Source File

SOURCE=.\CNewDlg.h
# End Source File
# Begin Source File

SOURCE=.\CNewWSDlg.h
# End Source File
# Begin Source File

SOURCE=.\CObjectFrm.h
# End Source File
# Begin Source File

SOURCE=.\CObjectView.h
# End Source File
# Begin Source File

SOURCE=.\CodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\CodeGenerators.h
# End Source File
# Begin Source File

SOURCE=.\CollaborationMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\CollaborationMultiObject.h
# End Source File
# Begin Source File

SOURCE=.\CollaborationObject.h
# End Source File
# Begin Source File

SOURCE=.\CollaborationObjectMessageText.h
# End Source File
# Begin Source File

SOURCE=.\CollaborationObjectPopup.h
# End Source File
# Begin Source File

SOURCE=.\CommentDlg.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\Communication.h
# End Source File
# Begin Source File

SOURCE=.\ComponentTemplate.h
# End Source File
# Begin Source File

SOURCE=.\ComponentText.h
# End Source File
# Begin Source File

SOURCE=.\Connection.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionInfoTuple.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionList.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionPopup.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionText.h
# End Source File
# Begin Source File

SOURCE=.\COODClassDoc.h
# End Source File
# Begin Source File

SOURCE=.\COODCntrlItem.h
# End Source File
# Begin Source File

SOURCE=.\COODCntrlItemList.h
# End Source File
# Begin Source File

SOURCE=.\COODCommonDoc.h
# End Source File
# Begin Source File

SOURCE=.\COODCommonFrm.h
# End Source File
# Begin Source File

SOURCE=.\COODCommonView.h
# End Source File
# Begin Source File

SOURCE=.\COODDoc.h
# End Source File
# Begin Source File

SOURCE=.\COODSrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\COODView.h
# End Source File
# Begin Source File

SOURCE=.\CPPClassPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CPPCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\CPPCommonCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\CPPMethodPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CPPVarPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsCodeGen.h
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsMacros.h
# End Source File
# Begin Source File

SOURCE=.\CProjectOptionsReverse.h
# End Source File
# Begin Source File

SOURCE=.\CResizableControlBar.h
# End Source File
# Begin Source File

SOURCE=.\CResizableDockBar.h
# End Source File
# Begin Source File

SOURCE=.\CResizableDockContext.h
# End Source File
# Begin Source File

SOURCE=.\CResizableDockState.h
# End Source File
# Begin Source File

SOURCE=.\CResizableEditDoc.h
# End Source File
# Begin Source File

SOURCE=.\CResizableEditView.h
# End Source File
# Begin Source File

SOURCE=.\CResizableEditViewBar.h
# End Source File
# Begin Source File

SOURCE=.\CResizableFloatWnd.h
# End Source File
# Begin Source File

SOURCE=.\CResizableMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\CResizableMiniDockFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\CResizableRectTracker.h
# End Source File
# Begin Source File

SOURCE=.\CResizableTreeBar.h
# End Source File
# Begin Source File

SOURCE=.\CResizeEditViewBarDocTemp.h
# End Source File
# Begin Source File

SOURCE=.\CSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSequenceFrm.h
# End Source File
# Begin Source File

SOURCE=.\CSequenceView.h
# End Source File
# Begin Source File

SOURCE=.\CSharpClassPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CSharpCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\CSharpMethodPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CSharpVarPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\CSplitterRect.h
# End Source File
# Begin Source File

SOURCE=.\CStateDoc.h
# End Source File
# Begin Source File

SOURCE=.\CStateFrm.h
# End Source File
# Begin Source File

SOURCE=.\CStateView.h
# End Source File
# Begin Source File

SOURCE=.\CTextDoc.h
# End Source File
# Begin Source File

SOURCE=.\CTextFrm.h
# End Source File
# Begin Source File

SOURCE=.\CTextView.h
# End Source File
# Begin Source File

SOURCE=.\CUseCaseDoc.h
# End Source File
# Begin Source File

SOURCE=.\CUseCaseFrm.h
# End Source File
# Begin Source File

SOURCE=.\CUseCaseView.h
# End Source File
# Begin Source File

SOURCE=.\CustomToolBar.h
# End Source File
# Begin Source File

SOURCE=.\CWndSpaceElt.h
# End Source File
# Begin Source File

SOURCE=.\DataMembersOption.h
# End Source File
# Begin Source File

SOURCE=.\Dependency.h
# End Source File
# Begin Source File

SOURCE=.\DependencyPopup.h
# End Source File
# Begin Source File

SOURCE=.\DeploymentMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\Diamond.h
# End Source File
# Begin Source File

SOURCE=.\Documents.h
# End Source File
# Begin Source File

SOURCE=.\EditableFigure.h
# End Source File
# Begin Source File

SOURCE=.\EditPopup.h
# End Source File
# Begin Source File

SOURCE=.\EndActivity.h
# End Source File
# Begin Source File

SOURCE=.\EventText.h
# End Source File
# Begin Source File

SOURCE=.\ExcludeRect.h
# End Source File
# Begin Source File

SOURCE=.\ExcludeRectList.h
# End Source File
# Begin Source File

SOURCE=.\Figure.h
# End Source File
# Begin Source File

SOURCE=.\FigureLibrary.h
# End Source File
# Begin Source File

SOURCE=.\FigureList.h
# End Source File
# Begin Source File

SOURCE=.\Figures.h
# End Source File
# Begin Source File

SOURCE=.\figutil.h
# End Source File
# Begin Source File

SOURCE=.\FinalState.h
# End Source File
# Begin Source File

SOURCE=.\FixedNamesTable.h
# End Source File
# Begin Source File

SOURCE=.\FontInfo.h
# End Source File
# Begin Source File

SOURCE=.\Frames.h
# End Source File
# Begin Source File

SOURCE=.\Generalization.h
# End Source File
# Begin Source File

SOURCE=.\GeneralizationPopup.h
# End Source File
# Begin Source File

SOURCE=.\HardwareNode.h
# End Source File
# Begin Source File

SOURCE=.\HWConnection.h
# End Source File
# Begin Source File

SOURCE=.\HWConnectionText.h
# End Source File
# Begin Source File

SOURCE=.\InitialState.h
# End Source File
# Begin Source File

SOURCE=.\InterfacePort.h
# End Source File
# Begin Source File

SOURCE=.\InterfacePortList.h
# End Source File
# Begin Source File

SOURCE=.\InterfacePortPopup.h
# End Source File
# Begin Source File

SOURCE=.\InterfacePortText.h
# End Source File
# Begin Source File

SOURCE=.\JavaClassPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\JavaCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\JavaMethodPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\JavaVarPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\KtgMacro.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\LineList.h
# End Source File
# Begin Source File

SOURCE=.\LineNode.h
# End Source File
# Begin Source File

SOURCE=.\LineNodeList.h
# End Source File
# Begin Source File

SOURCE=.\LinePopup.h
# End Source File
# Begin Source File

SOURCE=.\Lines.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\ListNode.h
# End Source File
# Begin Source File

SOURCE=.\macro_def.h
# End Source File
# Begin Source File

SOURCE=.\MemberFunctionsOption.h
# End Source File
# Begin Source File

SOURCE=.\MemberOptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\MemberPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\MessageFlow.h
# End Source File
# Begin Source File

SOURCE=.\MessageFlowPopup.h
# End Source File
# Begin Source File

SOURCE=.\MessageText.h
# End Source File
# Begin Source File

SOURCE=.\MessageTextPopup.h
# End Source File
# Begin Source File

SOURCE=.\MethodBodyDlg.h
# End Source File
# Begin Source File

SOURCE=.\NodeFigure.h
# End Source File
# Begin Source File

SOURCE=.\NodeFigureList.h
# End Source File
# Begin Source File

SOURCE=.\Note.h
# End Source File
# Begin Source File

SOURCE=.\NoteBoundary.h
# End Source File
# Begin Source File

SOURCE=.\NoteText.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPositionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObjectText.h
# End Source File
# Begin Source File

SOURCE=.\OneLineText.h
# End Source File
# Begin Source File

SOURCE=.\OOD.h
# End Source File
# Begin Source File

SOURCE=.\PackageCommentDlg.h
# End Source File
# Begin Source File

SOURCE=.\PackageLibrary.h
# End Source File
# Begin Source File

SOURCE=.\PackagePopup.h
# End Source File
# Begin Source File

SOURCE=.\PackagePropDlg.h
# End Source File
# Begin Source File

SOURCE=.\PackagePropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\PackageTemplate.h
# End Source File
# Begin Source File

SOURCE=.\PackageText.h
# End Source File
# Begin Source File

SOURCE=.\Popup.h
# End Source File
# Begin Source File

SOURCE=.\Popups.h
# End Source File
# Begin Source File

SOURCE=.\PropCommonDlg.h
# End Source File
# Begin Source File

SOURCE=.\QualificationText.h
# End Source File
# Begin Source File

SOURCE=.\QueryTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\RelationshipInfoTuple.h
# End Source File
# Begin Source File

SOURCE=.\RelationshipInfoTupleList.h
# End Source File
# Begin Source File

SOURCE=.\RelationTraverseDlg.h
# End Source File
# Begin Source File

SOURCE=.\RelationTraverseFrame.h
# End Source File
# Begin Source File

SOURCE=.\ResizeGlobalData.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoundBoxA.h
# End Source File
# Begin Source File

SOURCE=.\RoundBoxB.h
# End Source File
# Begin Source File

SOURCE=.\ScreenCaptureDlg.h
# End Source File
# Begin Source File

SOURCE=.\SequenceAsyncMessage.h
# End Source File
# Begin Source File

SOURCE=.\SequenceLanePopup.h
# End Source File
# Begin Source File

SOURCE=.\SequenceMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\SequenceMessageText.h
# End Source File
# Begin Source File

SOURCE=.\SequenceObject.h
# End Source File
# Begin Source File

SOURCE=.\SequenceObjectPopup.h
# End Source File
# Begin Source File

SOURCE=.\SequenceReturnMessage.h
# End Source File
# Begin Source File

SOURCE=.\SequenceSelfDelegation.h
# End Source File
# Begin Source File

SOURCE=.\SequenceSyncMessage.h
# End Source File
# Begin Source File

SOURCE=.\SimpleConnection.h
# End Source File
# Begin Source File

SOURCE=.\SlaveryText.h
# End Source File
# Begin Source File

SOURCE=.\SlaveryTextList.h
# End Source File
# Begin Source File

SOURCE=.\State.h
# End Source File
# Begin Source File

SOURCE=.\StateMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\StatePopup.h
# End Source File
# Begin Source File

SOURCE=.\StateText.h
# End Source File
# Begin Source File

SOURCE=.\StaticConnectionText.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SyncConditionText.h
# End Source File
# Begin Source File

SOURCE=.\SynchronizationBar.h
# End Source File
# Begin Source File

SOURCE=.\SynchronizationPopup.h
# End Source File
# Begin Source File

SOURCE=.\SystemBoundary.h
# End Source File
# Begin Source File

SOURCE=.\TabDlgWithName.h
# End Source File
# Begin Source File

SOURCE=.\TemplateClassTag.h
# End Source File
# Begin Source File

SOURCE=.\TemplateClassTagText.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\TextContent.h
# End Source File
# Begin Source File

SOURCE=.\TextLine.h
# End Source File
# Begin Source File

SOURCE=.\TipBoard.h
# End Source File
# Begin Source File

SOURCE=.\TipDialog.h
# End Source File
# Begin Source File

SOURCE=.\TipString.h
# End Source File
# Begin Source File

SOURCE=.\Transition.h
# End Source File
# Begin Source File

SOURCE=.\Triangle.h
# End Source File
# Begin Source File

SOURCE=.\Trigger.h
# End Source File
# Begin Source File

SOURCE=.\TriggerText.h
# End Source File
# Begin Source File

SOURCE=.\TupleText.h
# End Source File
# Begin Source File

SOURCE=.\TwoPointFigure.h
# End Source File
# Begin Source File

SOURCE=.\UnsignedLong.h
# End Source File
# Begin Source File

SOURCE=.\UseCase.h
# End Source File
# Begin Source File

SOURCE=.\UseCaseExtendsLink.h
# End Source File
# Begin Source File

SOURCE=.\UseCaseLink.h
# End Source File
# Begin Source File

SOURCE=.\UseCaseMainPopup.h
# End Source File
# Begin Source File

SOURCE=.\UseCaseText.h
# End Source File
# Begin Source File

SOURCE=.\UseCaseUsesLink.h
# End Source File
# Begin Source File

SOURCE=.\VCPPClassPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\VCPPClassPropMaps.h
# End Source File
# Begin Source File

SOURCE=.\VCPPCodeGenerator.h
# End Source File
# Begin Source File

SOURCE=.\VCPPMapEditor.h
# End Source File
# Begin Source File

SOURCE=.\VCPPMethodPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\VCPPVarPropGeneral.h
# End Source File
# Begin Source File

SOURCE=.\Views.h
# End Source File
# Begin Source File

SOURCE=.\VTerm.h
# End Source File
# Begin Source File

SOURCE=.\WidePackage.h
# End Source File
# Begin Source File

SOURCE=.\WideState.h
# End Source File
# Begin Source File

SOURCE=.\WideStateDlg.h
# End Source File
# Begin Source File

SOURCE=.\XCoord.h
# End Source File
# Begin Source File

SOURCE=.\YCoord.h
# End Source File
# Begin Source File

SOURCE=.\ZoomComboBox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COODDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\directory.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_acti.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_clas.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_comm.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_depl.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_inte.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_obje.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_sequ.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_stat.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_text.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_usec.ico
# End Source File
# Begin Source File

SOURCE=.\res\OOD.ico
# End Source File
# Begin Source File

SOURCE=.\res\OOD.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ood_srvr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_activ.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_class.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_colla.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_custo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_deplo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_seque.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_state.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_useca.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treebar_image.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ws_classview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ws_diagramview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ws_fileview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ws_infoview.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\OOD.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
