// **************************************************
// Custom code for UD103Form
// Created: 3/29/2016 11:19:46 AM
// **************************************************
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using Epicor.Mfg.BO;
using Epicor.Mfg.UI;
using Epicor.Mfg.UI.Adapters;
using Epicor.Mfg.UI.Customization;
using Epicor.Mfg.UI.ExtendedProps;
using Epicor.Mfg.UI.FormFunctions;
using Epicor.Mfg.UI.FrameWork;
using Epicor.Mfg.UI.Searches;
using System.Net.Mail;
using System.Reflection;
using System.Collections.Generic;
using Epicor.Mfg.Core;
using Epicor.Mfg.Lib;

public class Script
{
	// ** Wizard Insert Location - Do Not Remove 'Begin/End Wizard Added Module Level Variables' Comments! **
	// Begin Wizard Added Module Level Variables **

	private EpiDataView edvUD103;
	private EpiDataView edvUD103A;
	// End Wizard Added Module Level Variables **

	// Add Custom Module Level Variables Here **
	private Epicor.Mfg.Core.Session s;
	private DataTable OpenJobsGrid;
	private DataTable WarehouseGrid;
	private DataTable OpenJobs;
	private DataTable OpenOrdersGrid;
	private DataTable RMAs;
	private DataTable RMAsGrid;
	private DataTable POsGrid;
	private DataTable TFOs;
	private DataTable TFOsGrid;

	public void InitializeCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Variable Initialization' lines **
		// Begin Wizard Added Variable Initialization

		this.edvUD103 = ((EpiDataView)(this.oTrans.EpiDataViews["UD103"]));
		this.edvUD103.EpiViewNotification += new EpiViewNotification(this.edvUD103_EpiViewNotification);
		this.edvUD103A = ((EpiDataView)(this.oTrans.EpiDataViews["UD103A"]));
		this.edvUD103A.EpiViewNotification += new EpiViewNotification(this.edvUD103A_EpiViewNotification);
		this.UD103A_Column.ColumnChanged += new DataColumnChangeEventHandler(this.UD103A_AfterFieldChange);
		// End Wizard Added Variable Initialization

		// Begin Wizard Added Custom Method Calls

		this.epiButtonC1_CarFormSubmitOpen.Click += new System.EventHandler(this.epiButtonC1_CarFormSubmitOpen_Click);
		this.epiButtonC1_CarFormSendForReview.Click += new System.EventHandler(this.epiButtonC1_CarFormSendForReview_Click);
		this.epiButtonC1_PartsListAddNewPart.Click += new System.EventHandler(this.epiButtonC1_PartsListAddNewPart_Click);
		this.epiButtonC1_PopulateGrid.Click += new System.EventHandler(this.epiButtonC1_PopulateGrid_Click);
		this.epiBTT_Root_Add.Click += new System.EventHandler(this.epiBTT_Root_Add_Click);
		this.epiBTT_CA_Comm_Add.Click += new System.EventHandler(this.epiBTT_CA_Comm_Add_Click);
		this.epiBTT_Follow_Add.Click += new System.EventHandler(this.epiBTT_Follow_Add_Click);
		this.epiBTT_Pre_Add.Click += new System.EventHandler(this.epiBTT_Pre_Add_Click);
		this.epiBT_FOLLOW.Click += new System.EventHandler(this.epiBT_FOLLOW_Click);
		// End Wizard Added Custom Method Calls
		s = (Epicor.Mfg.Core.Session)UD103Form.Session;

		WarehouseGrid = new DataTable();
		WarehouseGrid.Columns.Add("Company", typeof(string));
		WarehouseGrid.Columns.Add("PartNum", typeof(string));
		WarehouseGrid.Columns.Add("Warehouse", typeof(string));
		WarehouseGrid.Columns.Add("On Hand Qty", typeof(string));
		WarehouseGrid.Columns.Add("Plant", typeof(string));

		OpenJobsGrid = new DataTable();
		OpenJobsGrid.Columns.Add("Company", typeof(string));
		OpenJobsGrid.Columns.Add("JobNum", typeof(string));
		OpenJobsGrid.Columns.Add("StartDate", typeof(string));
		OpenJobsGrid.Columns.Add("Prod Qty", typeof(string));
		OpenJobsGrid.Columns.Add("PartNum", typeof(string));

		OpenOrdersGrid = new DataTable();
		OpenOrdersGrid.Columns.Add("Company", typeof(string));
		OpenOrdersGrid.Columns.Add("Order", typeof(string));
		OpenOrdersGrid.Columns.Add("Line", typeof(string));
		OpenOrdersGrid.Columns.Add("Rel", typeof(string));
		OpenOrdersGrid.Columns.Add("PartNum", typeof(string));

		RMAsGrid = new DataTable();
		RMAsGrid.Columns.Add("Company", typeof(string));
		RMAsGrid.Columns.Add("RMANum", typeof(string));
		RMAsGrid.Columns.Add("RMALine", typeof(string));
		RMAsGrid.Columns.Add("Order", typeof(string));
		RMAsGrid.Columns.Add("Line", typeof(string));
		RMAsGrid.Columns.Add("PartNum", typeof(string));

		POsGrid = new DataTable();
		POsGrid.Columns.Add("Company", typeof(string));
		POsGrid.Columns.Add("PONum", typeof(string));
		POsGrid.Columns.Add("POLine", typeof(string));
		POsGrid.Columns.Add("PORel", typeof(string));
		POsGrid.Columns.Add("DueDate", typeof(string));
		POsGrid.Columns.Add("PartNum", typeof(string));

		TFOsGrid = new DataTable();
		TFOsGrid.Columns.Add("Company", typeof(string));
		TFOsGrid.Columns.Add("Order", typeof(string));
		TFOsGrid.Columns.Add("Line", typeof(string));
		TFOsGrid.Columns.Add("PartNum", typeof(string));

		epiUltraGridC1_Jobs.DataSource = OpenJobsGrid;
		epiUltraGridC1_Jobs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Inventory.DataSource = WarehouseGrid;
		epiUltraGridC1_Inventory.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Orders.DataSource = OpenOrdersGrid;
		epiUltraGridC1_Orders.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_RMAs.DataSource = RMAsGrid;
		epiUltraGridC1_RMAs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
		
		epiUltraGridC1_TFOs.DataSource = TFOsGrid;
		epiUltraGridC1_TFOs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
		
		epiUltraGridC1_POs.DataSource = POsGrid;
		epiUltraGridC1_POs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Parts.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
	}

	public void DestroyCustomCode()
	{
		// ** Wizard Insert Location - Do not delete 'Begin/End Wizard Added Object Disposal' lines **
		// Begin Wizard Added Object Disposal

		this.epiButtonC1_CarFormSubmitOpen.Click -= new System.EventHandler(this.epiButtonC1_CarFormSubmitOpen_Click);
		this.epiButtonC1_CarFormSendForReview.Click -= new System.EventHandler(this.epiButtonC1_CarFormSendForReview_Click);
		this.edvUD103.EpiViewNotification -= new EpiViewNotification(this.edvUD103_EpiViewNotification);
		this.edvUD103 = null;
		this.epiButtonC1_PartsListAddNewPart.Click -= new System.EventHandler(this.epiButtonC1_PartsListAddNewPart_Click);
		this.edvUD103A.EpiViewNotification -= new EpiViewNotification(this.edvUD103A_EpiViewNotification);
		this.edvUD103A = null;
		this.UD103A_Column.ColumnChanged -= new DataColumnChangeEventHandler(this.UD103A_AfterFieldChange);
		this.epiButtonC1_PopulateGrid.Click -= new System.EventHandler(this.epiButtonC1_PopulateGrid_Click);
		this.epiBTT_Root_Add.Click -= new System.EventHandler(this.epiBTT_Root_Add_Click);
		this.epiBTT_CA_Comm_Add.Click -= new System.EventHandler(this.epiBTT_CA_Comm_Add_Click);
		this.epiBTT_Follow_Add.Click -= new System.EventHandler(this.epiBTT_Follow_Add_Click);
		this.epiBTT_Pre_Add.Click -= new System.EventHandler(this.epiBTT_Pre_Add_Click);
		this.epiBT_FOLLOW.Click -= new System.EventHandler(this.epiBT_FOLLOW_Click);
		// End Wizard Added Object Disposal

		// Begin Custom Code Disposal

		// End Custom Code Disposal
		s = null;
		OpenJobsGrid = null;
		WarehouseGrid = null;
		OpenJobs = null;
		OpenOrdersGrid = null;
		RMAs = null;
		RMAsGrid = null;
		POsGrid = null;
		TFOs = null;
		TFOsGrid = null;
	}



	private void epiButtonC1_CarFormSubmitOpen_Click(object sender, System.EventArgs args)
	{
		

		string AssignedManager = string.Empty;
		//Set Car Manager based on below.
		//	1. If Cur-Company & Cur-Plant = CIC68322MfgSys then UD103.ShortChar03 = Anicol
		if(s.CompanyID == "CIC68322" && s.PlantID=="MfgSys")
			{
			//edvUD103.dataView[edvUD103.Row]["ShortChar03"] = "Anicol";
			AssignedManager = "anicol";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "CT";
			}
		//	2. If Cur-Company & Cur-Plant = CIC6832210 then UD103.ShortChar03 = emcane
		else if(s.CompanyID == "CIC68322" && s.PlantID=="03")
			{
			AssignedManager = "emcane";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "IR";
			}
		//	3. If Cur-Company & Cur-Plant = CIC6832204 then UD103.ShortChar03 = anicol
		else if(s.CompanyID == "CIC68322" && s.PlantID=="04")
			{
			AssignedManager = "anicol";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "WS";
			}
		//	4. If Cur-Company & Cur-Plant = CIC6832205 then UD103.ShortChar03 = Jonp
		else if(s.CompanyID == "CIC68322" && s.PlantID=="05")
			{
			AssignedManager = "Jonp";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "TX";
			}
		//	5. If Cur-Company & Cur-Plant = CIC6832206 then UD103.ShortChar03 = ibutcher
		else if(s.CompanyID == "CIC68322" && s.PlantID=="06")
			{
			AssignedManager = "ibutcher";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "MX";
			}
		//	6. If Cur-Company & cur-Plant = 10MfgSys then UD103.ShortChar03 = plowe
		else if(s.CompanyID == "10" && s.PlantID=="MfgSys")
			{
			AssignedManager = "plowe";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "UK";
			}
		//	7. If Cur-Company & cur-Plant = 20MfgSys then UD103.ShortChar03 = mroat
		else if(s.CompanyID == "MfgSys" && s.PlantID=="MfgSys")
			{
			AssignedManager = "mroat";
			edvUD103.dataView[edvUD103.Row]["Character10"] = "PL";
			}
		//	8. ** Double Check so you can't assign a CAR to yourself, and be a manager
		//	9. if UD103.Company = CIC68322 and UD103.ShortChar03 = UD103.shortchar01 Then UD103.shortchar03 = gwarner
		if(s.CompanyID=="CIC68322" && AssignedManager == (string)edvUD103.dataView[edvUD103.Row]["ShortChar01"])
			{
			AssignedManager = "gwarner";
			}
		//	10. if UD103.Company = 10  and UD103.ShortChar03 = UD103.shortchar01 then = UD103.shortchar03 = gwarner
		 if(s.CompanyID=="10" && AssignedManager == (string)edvUD103.dataView[edvUD103.Row]["ShortChar01"])
			{
			AssignedManager = "gwarner";
			}
		//	11. if UD103.Company = 20 and  UD103.ShortChar03 = UD103.shortchar01 Then UD103.shortchar03 = Plowe
		 if(s.CompanyID=="20" && AssignedManager == (string)edvUD103.dataView[edvUD103.Row]["ShortChar01"])
			AssignedManager = "plowe";

		if(AssignedManager == string.Empty)
		{
			MessageBox.Show("Unable to assign a manager to this, Unable to submit");
			return;
		}
		edvUD103.dataView[edvUD103.Row].BeginEdit();
		//Stamp time 2:00PM 1-APR-16 Cur-User in UD103.ShortChar04
		edvUD103.dataView[edvUD103.Row]["ShortChar04"] = string.Format("{1} {0:HH:mmtt dd-MMM-yy}", DateTime.Now, s.UserID);
		//UD103.ShortChar06 = "OPEN"
		edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "OPEN";
		//UD103.Date01 = NOW()
		edvUD103.dataView[edvUD103.Row]["Date01"] = DateTime.Now;
		// UD103.Date02 = Today.AddDays(30)
		edvUD103.dataView[edvUD103.Row]["Date02"] = DateTime.Now.AddDays(30);
		//Set Car Manager.
		edvUD103.dataView[edvUD103.Row]["ShortChar03"] = AssignedManager;
         //Send Email TO: user > UD103.ShortChar01
         //Send Email CC: user > UD103.ShortChar03
		 
		 // Set Plant based on CUR-PLANT
		
		 //edvUD103.dataView[edvUD103.Row]["Character10"] = s.PlantID;

		List<string> address = new List<string>();
		DataTable AddressTable = GetUserFileRows();
		foreach(DataRow r in AddressTable.Rows)
		{
			if((string)r["UserFile.DCDUserID"] == (string)edvUD103.dataView[edvUD103.Row]["ShortChar01"] || (string)r["UserFile.DCDUserID"] == (string)edvUD103.dataView[edvUD103.Row]["ShortChar03"])
			{
				address.Add((string)r["UserFile.EmailAddress"]);
			}
		}
		string strSubject = string.Format("CAR# {0}, Needs your attention!", edvUD103.dataView[edvUD103.Row]["KEY1"]);
		string strBody = string.Format("A CAR has been generated and issued to {0}. You have until {1:dd-MMM-yyyy} to submit this CAR back to {2} for review.", edvUD103.dataView[edvUD103.Row]["ShortChar02"], edvUD103.dataView[edvUD103.Row]["Date02"], edvUD103.dataView[edvUD103.Row]["ShortChar03"]);

		SendEmail(address, strSubject,strBody);
		address = null;
		edvUD103.dataView[edvUD103.Row].EndEdit();
	}

	private void epiButtonC1_CarFormSendForReview_Click(object sender, System.EventArgs args)
	{
		edvUD103.dataView[edvUD103.Row].BeginEdit();
		//1. UD103.ShortChar06 = "FOLLOW UP"
		edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "FOLLOW UP";
		//2. Send Email TO: UD103.ShortChar03
		List<string> address = new List<string>();
		DataTable AddressTable = GetUserFileRows();
		foreach(DataRow r in AddressTable.Rows)
		{
			if((string)r["UserFile.DCDUserID"] == (string)edvUD103.dataView[edvUD103.Row]["ShortChar03"])
			{
				address.Add((string)r["UserFile.EmailAddress"]);
			}
		}

		string strSubject = string.Format("CAR# {0}, Has Been Submited for Approval!", edvUD103.dataView[edvUD103.Row]["KEY1"]);
		string strBody = string.Format("CAR {0} has been submitted back to {1} for review and approval.  Based on the implementation date on the CAR, you have until {2:dd-MMM-yyyy} to complete your follow up and close the CAR.", edvUD103.dataView[edvUD103.Row]["Key1"], edvUD103.dataView[edvUD103.Row]["ShortChar03"],edvUD103.dataView[edvUD103.Row]["Date04"]);
	
		SendEmail(address, strSubject,strBody);
		address = null;
		//3. UD103.Date04  = UD103.Date03 + 30 Days (if Date03 is empty, set date 03 to NOW)
		try{
			edvUD103.dataView[edvUD103.Row]["Date04"] = ((DateTime)edvUD103.dataView[edvUD103.Row]["Date03"]).AddDays(30);
		}
		catch
		{
			edvUD103.dataView[edvUD103.Row]["Date04"] = DateTime.Now.AddDays(30);
		}
		edvUD103.dataView[edvUD103.Row].EndEdit();
	}

	private void edvUD103_EpiViewNotification(EpiDataView view, EpiNotifyArgs args)
	{
		// ** Argument Properties and Uses **
		// view.dataView[args.Row]["FieldName"]
		// args.Row, args.Column, args.Sender, args.NotifyType
		// NotifyType.Initialize, NotifyType.AddRow, NotifyType.DeleteRow, NotifyType.InitLastView, NotifyType.InitAndResetTreeNodes
		if ((args.NotifyType == EpiTransaction.NotifyType.Initialize))
		{
			if ((args.Row > -1))
			{
				//GetData((string)edvUD103.dataView[edvUD103.Row]["Character06"], OpenJobsGrid);
				//GetData((string)edvUD103.dataView[edvUD103.Row]["Character07"], WarehouseGrid);
				//PopulateGrids(true);
				epiUltraGridC1_Jobs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_Inventory.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_Orders.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_RMAs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_TFOs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_POs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				epiUltraGridC1_Parts.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
				
			}
			else
			{
				while(OpenJobsGrid.Rows.Count > 0)OpenJobsGrid.Rows[0].Delete();
				while(WarehouseGrid.Rows.Count > 0)WarehouseGrid.Rows[0].Delete();
				while(OpenOrdersGrid.Rows.Count > 0)OpenOrdersGrid.Rows[0].Delete();
				while(RMAsGrid.Rows.Count > 0)RMAsGrid.Rows[0].Delete();
				while(POsGrid.Rows.Count > 0)POsGrid.Rows[0].Delete();
				while(TFOsGrid.Rows.Count > 0)TFOsGrid.Rows[0].Delete();
			}
		}
	}

    private void SendEmail(List<string> addresses, string subject, string body) {
        BOReader reader = new BOReader(s.ConnectionPool);
        DataSet smtpDataSet = reader.GetRows("Company", string.Format("Company='{0}'", s.CompanyID), "SMTPServer,SMTPPort,EmailFromAddr");

        MailMessage message = new MailMessage();
        message.From = new MailAddress(smtpDataSet.Tables[0].Rows[0][2].ToString());
        message.Subject = subject;
        message.Body = body;

        foreach (string a in addresses)
            message.To.Add(a);

        string smtpHost = smtpDataSet.Tables[0].Rows[0][0].ToString();
        int smtpPort = Convert.ToInt32(smtpDataSet.Tables[0].Rows[0][1]);
        SmtpClient smtp = new SmtpClient(smtpHost, smtpPort);
        smtp.Send(message);
		smtp = null;
		smtpDataSet = null;
		reader = null;
    }

    private DataTable GetUserFileRows() {
		return CallDynamicQuery("CIC68322-GetEmailAddress", null);
    }

	string AddPartNum = string.Empty;
	string AddPartDescription = string.Empty;
	string AddPartClass = string.Empty;
	string AddProdGroup = string.Empty;
	bool AddingPartInCode = false;
	private void epiButtonC1_PartsListAddNewPart_Click(object sender, System.EventArgs args)
	{
		AddPartNum = AddPartDescription = AddPartClass = AddProdGroup = string.Empty;
		SearchOnPartAdapterShowDialog();
		if(AddPartNum != string.Empty)
		{
			DisplayData(string.Format("Adding part {0} Desc:{1} Class:{2} Group:{3}", AddPartNum, AddPartDescription, AddPartClass, AddProdGroup));
			AddingPartInCode = true;
			oTrans.GetNewChild();
			edvUD103A.dataView[edvUD103A.Row].BeginEdit();
			edvUD103A.dataView[edvUD103A.Row]["ChildKey1"] = AddPartNum;
			edvUD103A.dataView[edvUD103A.Row]["Character01"] = AddPartDescription;
			edvUD103A.dataView[edvUD103A.Row]["ShortChar01"] = AddPartClass;
			edvUD103A.dataView[edvUD103A.Row]["ShortChar02"] = AddProdGroup;
			edvUD103A.dataView[edvUD103A.Row].EndEdit();
			AddingPartInCode = false;
			oTrans.Update();
		}
	}

	private void SearchOnPartAdapterShowDialog()
	{
		bool recSelected;
		string whereClause = string.Empty;
		System.Data.DataSet dsPartAdapter = Epicor.Mfg.UI.FormFunctions.SearchFunctions.listLookup(this.oTrans, "PartAdapter", out recSelected, true, whereClause);
		if (recSelected)
		{
			System.Data.DataRow adapterRow = dsPartAdapter.Tables[0].Rows[0];
			DisplayData("PartNum");
			AddPartNum = (string)adapterRow["PartNum"];
			DisplayData("PartDescription");
			AddPartDescription = (string)adapterRow["PartDescription"];
			DisplayData("ProdCode");
			AddProdGroup = (string)adapterRow["ProdCode"];
			DisplayData("ClassID");
			AddPartClass = (string)adapterRow["ClassID"];
		}
		dsPartAdapter = null;
	}
	private bool SearchOnPartAdapterNoDialog(string partnum)
	{
		if(AddingPartInCode) return false;
		bool recSelected;
		string whereClause = string.Format("(PartNum='{0}')", partnum);
		System.Data.DataSet dsPartAdapter = Epicor.Mfg.UI.FormFunctions.SearchFunctions.listLookup(this.oTrans, "PartAdapter", out recSelected, false, whereClause);
		if (recSelected)
		{
			System.Data.DataRow adapterRow = dsPartAdapter.Tables[0].Rows[0];

			DisplayData("NoDialog PartNum");
			AddPartNum = (string)adapterRow["PartNum"];
			DisplayData("NoDialog PartDescription");
			AddPartDescription = (string)adapterRow["PartDescription"];
			DisplayData("NoDialog ProdCode");
			AddProdGroup = (string)adapterRow["ProdCode"];
			DisplayData("NoDialog ClassID");
			AddPartClass = (string)adapterRow["ClassID"];
		}
		dsPartAdapter = null;
		return recSelected;
	}

	private void edvUD103A_EpiViewNotification(EpiDataView view, EpiNotifyArgs args)
	{
		// ** Argument Properties and Uses **
		// view.dataView[args.Row]["FieldName"]
		// args.Row, args.Column, args.Sender, args.NotifyType
		// NotifyType.Initialize, NotifyType.AddRow, NotifyType.DeleteRow, NotifyType.InitLastView, NotifyType.InitAndResetTreeNodes
		if ((args.NotifyType == EpiTransaction.NotifyType.AddRow))
		{
			if ((args.Row > -1))
			{
			}
		}
	}

	private void UD103A_AfterFieldChange(object sender, DataColumnChangeEventArgs args)
	{
		// ** Argument Properties and Uses **
		// args.Row["FieldName"]
		// args.Column, args.ProposedValue, args.Row
		// Add Event Handler Code
		switch (args.Column.ColumnName)
		{
			case "ChildKey1":
				if(AddingPartInCode)return;
				AddPartNum = AddPartDescription = AddPartClass = AddProdGroup = string.Empty;
				
				if(SearchOnPartAdapterNoDialog((string)edvUD103A.dataView[edvUD103A.Row]["ChildKey1"]))
				{
					edvUD103A.dataView[edvUD103A.Row].BeginEdit();
//					edvUD103A.dataView[edvUD103A.Row]["ChildKey1"] = AddPartNum;
					edvUD103A.dataView[edvUD103A.Row]["Character01"] = AddPartDescription;
					edvUD103A.dataView[edvUD103A.Row]["ShortChar01"] = AddPartClass;
					edvUD103A.dataView[edvUD103A.Row]["ShortChar02"] = AddProdGroup;
					edvUD103A.dataView[edvUD103A.Row].EndEdit();
				}
				else
				{
					MessageBox.Show("That is not a valid part number");
				}
				break;
		}
	}
	private void UD103Form_Load(object sender, EventArgs args)
	{
//		EpiTreeViewPanel panel = (EpiTreeViewPanel)csm.GetNativeControlReference("46c8ee42-a6f1-468b-95ba-6dfc13223ee2").Parent;
//		Infragistics.Win.UltraWinDock.DockableWindow dock = (Infragistics.Win.UltraWinDock.DockableWindow)panel.Parent;
//		Infragistics.Win.UltraWinDock.DockableControlPane pane = dock.Pane;
//		pane.Close();

		        edvUD103.dataView.Table.Columns["Character02"].ExtendedProperties["ReadOnly"] = true;
		        edvUD103.dataView.Table.Columns["Character03"].ExtendedProperties["ReadOnly"] = true;
		        edvUD103.dataView.Table.Columns["Character04"].ExtendedProperties["ReadOnly"] = true;
		        edvUD103.dataView.Table.Columns["Character05"].ExtendedProperties["ReadOnly"] = true;
		        edvUD103.dataView.Table.Columns["ShortChar03"].ExtendedProperties["ReadOnly"] = true;
		        edvUD103.dataView.Table.Columns["ShortChar01"].ExtendedProperties["ReadOnly"] = true;


				//Cool trick to create LABELS
				//Root Cause epiLabelC16
				string AS1 = "One method to perform a Root Cause Analysis is to ask the question “Why?” five times, starting with “Why did the discrepancy happen”";
				string AS2 = " o   Ex. Why was the cover not sewn per the pattern?";
				string AS3 = "Another method to perform a Root Cause Analysis is to fill out a Fish Bone Diagram";
				string AS4 = " o   See QA-F-017 in the AS9100 vault in Meridian";
				epiLabelC15.Text = string.Format("{1}{0}{2}{0}{3}{0}{4}",Environment.NewLine,AS1,AS2,AS3,AS4);
				epiLabelC15.TextAlign = System.Drawing.ContentAlignment.TopLeft;

				//Corrective Action epiLabelC16
				string BS1 = "Any actions done to contain the problem should be listed in this section. Example of Containment actions";
				string BS2 = " o   All stock and in-transit product will be verified";
				string BS3 = " o   The part will be put on hold in Epicor to hold shipments";
				string BS4 = " o   All inventory will been quarantined and will be reviewed by Quality";
				string BS5 = "Once the Containment Actions are complete, the comments section should be updated with the findings/results.  The Corrective Action should immediately fix the problem in order to prevent any more escapes.  Example of Corrective Action.";
				string BS6 = " o   A Quality Alert will be posted to ensure all are aware of the discrepancy";
				string BS7 = " o   Parts will be reworked to meet the drawing";
				epiLabelC16.Text = string.Format("{1}{0}{2}{0}{3}{0}{4}{0}{5}{0}{6}{0}{7}",Environment.NewLine,BS1,BS2,BS3,BS4,BS5,BS6,BS7);
				epiLabelC16.TextAlign = System.Drawing.ContentAlignment.TopLeft;

				//Corrective Action epiLabelC17
				string CS1 = "The Preventive Action should directly answer the question “What needs to be done to ensure the discrepancy does not happen again?”  Example of Preventive Action.";
				string CS2 = " o   An ECR will be generated for this part, and all similar parts, to update the manufacturing documents";
				string CS3 = " o   The procedure will be updated and all relating departments will be trained on the new procedure";
				epiLabelC17.Text = string.Format("{1}{0}{2}{0}{3}",Environment.NewLine,CS1,CS2,CS3);
				epiLabelC17.TextAlign = System.Drawing.ContentAlignment.TopLeft;

				//Corrective Action epiLabelC18
				string DS1 = "The Follow Up must review the Preventive and Corrective Actions to ensure they were effective";
				string DS2 = " o   Ex. No more rejections have occurred since the implementation of the Preventive Action";
				string DS3 = "All evidence of the implementation of the Corrective and Preventive Actions must be verified and attached to the CAR";
				string DS4 = " o   Ex. Training documentation of a new/updated procedure needs to be attached";
				epiLabelC18.Text = string.Format("{1}{0}{2}{0}{3}",Environment.NewLine,DS1,DS2,DS3,DS4);
				epiLabelC18.TextAlign = System.Drawing.ContentAlignment.TopLeft;



	}

	private void PopulateGrids(bool OrderRmaTOPO_ONLY)
	{
		
		if(!OrderRmaTOPO_ONLY)while(OpenJobsGrid.Rows.Count > 0)OpenJobsGrid.Rows[0].Delete();
		if(!OrderRmaTOPO_ONLY)while(WarehouseGrid.Rows.Count > 0)WarehouseGrid.Rows[0].Delete();
		while(OpenOrdersGrid.Rows.Count > 0)OpenOrdersGrid.Rows[0].Delete();
		while(RMAsGrid.Rows.Count > 0)RMAsGrid.Rows[0].Delete();
		while(POsGrid.Rows.Count > 0)POsGrid.Rows[0].Delete();
		while(TFOsGrid.Rows.Count > 0)TFOsGrid.Rows[0].Delete();
		DisplayData("PopulateGrids Start");
		DataTable t = null;
		DataView dv = null;

		string whereclause = string.Empty;
		DisplayData("PopulateGrids dataView");
		foreach(DataRowView r in edvUD103A.dataView)
		{
			string partnum = (string)r["ChildKey1"];
			DisplayData("PopulateGrids dataView PartWhseSearch_ECR");
	        t = CallDynamicQuery("CIC68322-PartWhseSearch_ECR", new List<string>(new string[]{string.Format("PartNum,string,{0}", partnum)}));
			DisplayData("PopulateGrids dataView PartWhseSearch_ECR ROWS");
			foreach(DataRow w in t.Rows)
			{
	    		if (!OrderRmaTOPO_ONLY && Convert.ToInt32((decimal)w["PartWhse.OnHandQty"]) != 0)
				{
					DataRow newrow = WarehouseGrid.NewRow();
					DisplayData("PartWhse.Company");
					newrow["Company"] = (string)w["Company"];
					DisplayData("PartWhse.PartNum");
					newrow["PartNum"] = (string)w["PartWhse.PartNum"];
					DisplayData("PartWhse.WarehouseCode");
					newrow["Warehouse"] = (string)w["PartWhse.WarehouseCode"];
					DisplayData("PartWhse.OnHandQty");
					newrow["On Hand Qty"] = ((decimal)w["PartWhse.OnHandQty"]).ToString();
					DisplayData("PartWhse.Plant");
					newrow["Plant"] = (string)w["Warehse.Plant"];
					WarehouseGrid.Rows.Add(newrow);
				}
			}

			DisplayData("PopulateGrids dataView CAR_OpenOrders");
	        t = CallDynamicQuery("CIC68322-CAR_OpenOrders", new List<string>(new string[]{string.Format("PartNum,string,{0}", partnum)}));
			DisplayData("PopulateGrids dataView CAR_OpenOrders ROWS");
			foreach(DataRow w in t.Rows)
			{
				DataRow newrow = OpenOrdersGrid.NewRow();
				newrow["Company"] = (string)w["OrderRel.Company"];
				newrow["Order"] = ((int)w["OrderRel.OrderNum"]).ToString();
				newrow["Line"] = ((int)w["OrderRel.OrderLine"]).ToString();
				newrow["Rel"] = ((int)w["OrderRel.OrderRelNum"]).ToString();
				newrow["PartNum"] = (string)w["OrderRel.PartNum"];
				OpenOrdersGrid.Rows.Add(newrow);
			}

			DisplayData("PopulateGrids dataView CAR_OpenPOs");
	        t = CallDynamicQuery("CIC68322-CAR_OpenPOs", new List<string>(new string[]{string.Format("PartNum,string,{0}", partnum)}));
			DisplayData("PopulateGrids dataView CAR_OpenPOs ROWS");
			foreach(DataRow w in t.Rows)
			{
				if(!(bool)w["PORel.OpenRelease"])continue;
				DataRow newrow = POsGrid.NewRow();
				newrow["Company"] = (string)w["PORel.Company"];
				newrow["PONum"] = ((int)w["PORel.PONum"]).ToString();
				newrow["POLine"] = ((int)w["PORel.POLine"]).ToString();
				newrow["PORel"] = ((int)w["PORel.PORelNum"]).ToString();
				newrow["DueDate"] = ((DateTime)w["PORel.DueDate"]).ToString();
				newrow["PartNum"] = (string)w["PODetail.PartNum"];
				POsGrid.Rows.Add(newrow);
			}
			//
			whereclause += string.Format("{0}PartNum='{1}'", (whereclause.Length > 0? " OR ": ""), partnum);
		}

		DisplayData("PopulateGrids Jobs");
		if(OpenJobs == null)OpenJobs = CallDynamicQuery("CIC68322-AffectedJobs", null);
		if(!OrderRmaTOPO_ONLY)
		{
			DisplayData("PopulateGrids dataView OpenJobsGrid");
			dv = new DataView(OpenJobs);
			dv.RowFilter = whereclause.Replace("PartNum", "JobHead.PartNum");
	//		string x = string.Empty;
	//		foreach(DataColumn c in OpenJobs.Columns)
	//		{
	//			x += string.Format("{0}{1}", c.ColumnName, Environment.NewLine);
	//		}
	//		MessageBox.Show(x);
			foreach(DataRowView r in dv)
			{
				DataRow nr = OpenJobsGrid.NewRow();
				nr["Company"] = (string)r["Company"];
				nr["JobNum"] = (string)r["JobHead.JobNum"];
				nr["StartDate"] = ((DateTime)r["JobHead.StartDate"]).ToString();
				nr["Prod Qty"] = ((decimal)r["JobHead.ProdQty"]).ToString();
				nr["PartNum"] = (string)r["JobHead.PartNum"];
				OpenJobsGrid.Rows.Add(nr);
			}
		}

		DisplayData("PopulateGrids RMAs");
		if(RMAs == null)RMAs = CallDynamicQuery("CIC68322-CAR_RMASearch", null);
		DisplayData("PopulateGrids dataView RMAs");
		dv = new DataView(RMAs);
		dv.RowFilter = whereclause.Replace("PartNum", "RMADtl.PartNum");
		foreach(DataRowView r in dv)
		{
			DataRow nr = RMAsGrid.NewRow();
			nr["Company"] = (string)r["RMADtl.Company"];
			nr["RMANum"] = ((int)r["RMADtl.RMANum"]).ToString();
			nr["RMALine"] = ((int)r["RMADtl.RMALine"]).ToString();
			nr["Order"] = ((int)r["RMADtl.OrderNum"]).ToString();
			nr["Line"] = ((int)r["RMADtl.OrderLine"]).ToString();
			nr["PartNum"] = (string)r["RMADtl.PartNum"];
			RMAsGrid.Rows.Add(nr);
		}

		DisplayData("PopulateGrids TFOs");
		if(TFOs == null)TFOs = CallDynamicQuery("CIC68322-CAR_TransferOrders", null);
		DisplayData("PopulateGrids dataView TFOs");
		dv = new DataView(TFOs);
		dv.RowFilter = whereclause.Replace("PartNum", "TFOrdDtl.PartNum");
		foreach(DataRowView r in dv)
		{
			DataRow nr = TFOsGrid.NewRow();
			nr["Company"] = (string)r["TFOrdDtl.Company"];
			nr["Order"] = (string)r["TFOrdDtl.TFOrdNum"];
			nr["Line"] = ((int)r["TFOrdDtl.TFOrdLine"]).ToString();
			nr["PartNum"] = (string)r["TFOrdDtl.PartNum"];
			TFOsGrid.Rows.Add(nr);
		}

		epiUltraGridC1_Jobs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Inventory.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Orders.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_RMAs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
		
		epiUltraGridC1_TFOs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
		
		epiUltraGridC1_POs.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;

		epiUltraGridC1_Parts.DisplayLayout.AutoFitStyle = Infragistics.Win.UltraWinGrid.AutoFitStyle.ResizeAllColumns;
		
		DisplayData("PopulateGrids end");
		if(!OrderRmaTOPO_ONLY)SaveData();
	}

	private void SaveData()
	{
		edvUD103.dataView[edvUD103.Row].BeginEdit();
		edvUD103.dataView[edvUD103.Row]["Character06"] = DataTableToString(OpenJobsGrid);
		edvUD103.dataView[edvUD103.Row]["Character07"] = DataTableToString(WarehouseGrid);
		edvUD103.dataView[edvUD103.Row].EndEdit();
	}

	private string DataTableToString(DataTable t)
	{
		string rs = string.Empty;
		for(int row = 0; row < t.Rows.Count; ++row)
		{
			if(row > 0)rs+="~";
			for(int col = 0; col < t.Columns.Count; col++)
			{
				if(col > 0)rs += ",";
				rs += t.Rows[row][col].ToString();
			}
		}
		return rs;
	}


	private void GetData(string x, DataTable t)
	{
	    List<string> rv = new List<string>();
	    foreach (string s in x.Split('~'))
		{
			int c = 0;
			DataRow r = t.NewRow();
			foreach(string s1 in s.Split(','))
			{
				r[c] = s1;
	        	c++;
			}
			t.Rows.Add(r);
		}
	}

	private void DisplayData(string x)
	{
		oTrans.PushStatusText(x, false);
	}

	private DataTable CallDynamicQuery(string QueryID, List<string> Parameters )
	{

		DynamicQueryAdapter d = new DynamicQueryAdapter(this.oTrans);
		d.BOConnect();
		if(Parameters != null){
			d.GetByID(QueryID);
			Epicor.Mfg.BO.QueryExecutionDataSet ds = d.GetQueryExecutionParameters(d.QueryDesignData);
			foreach(String s in Parameters)
			{
				string ParameterName, ValueType, ParameterValue;
				ParameterName = s.Split(',')[0];
				ValueType = s.Split(',')[1];
				ParameterValue = s.Split(',')[2];
				DataRow r = ds.Tables["ExecutionParameter"].NewRow();
				r["ParameterName"] = ParameterName;
				r["ParameterValue"] = ParameterValue;
				r["ValueType"] = ValueType;
				r["IsEmpty"] = false;
				r["RowIdent"] = string.Empty;
				r["RowMod"] = "A";
				ds.Tables["ExecutionParameter"].Rows.Add(r);
			}
			string resultFieldList = string.Empty;
			int topNRecords = 0;
			bool hasMoreRecords;
			d.ExecuteByIDParametrized(QueryID, ds, "", topNRecords,out hasMoreRecords);
		}
		else
			d.ExecuteByID(QueryID);
		DataTable ReturnDataTable = d.QueryResults.Tables["Results"];
		d.Dispose();
		d = null;
		return ReturnDataTable;
	}


	private void epiButtonC1_PopulateGrid_Click(object sender, System.EventArgs args)
	{
		PopulateGrids(false);
	}

	private void epiBTT_Root_Add_Click(object sender, System.EventArgs args)
	{
		string User_TnD = string.Format("{0:HH:mmtt dd-MMM-yyyy} {1}", DateTime.Now, s.UserID);
		string addfieldContents = string.Empty;

		addfieldContents = string.Format("{3}{0}{3}{1}{3}{2}{3}",
			"---------------------",
			User_TnD,
			txt_Root_Add.Text,
			Environment.NewLine);

			edvUD103.dataView[edvUD103.Row]["Character02"] += addfieldContents;
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "In Progress";

	}

	private void epiBTT_CA_Comm_Add_Click(object sender, System.EventArgs args)
	{
		string User_TnD = string.Format("{0:HH:mmtt dd-MMM-yyyy} {1}", DateTime.Now, s.UserID);
		string addfieldContents = string.Empty;

		addfieldContents = string.Format("{3}{0}{3}{1}{3}{2}{3}",
			"---------------------",
			User_TnD,
			txt_CA_Comm_Add.Text,
			Environment.NewLine);

			edvUD103.dataView[edvUD103.Row]["Character03"] += addfieldContents;
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "In Progress";
	}

	private void epiBTT_Pre_Add_Click(object sender, System.EventArgs args)
	{
		string User_TnD = string.Format("{0:HH:mmtt dd-MMM-yyyy} {1}", DateTime.Now, s.UserID);
		string addfieldContents = string.Empty;

		addfieldContents = string.Format("{3}{0}{3}{1}{3}{2}{3}",
			"---------------------",
			User_TnD,
			txt_Pre_Add.Text,
			Environment.NewLine);

			edvUD103.dataView[edvUD103.Row]["Character05"] += addfieldContents;
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "In Progress";

	}

	private void epiBTT_Follow_Add_Click(object sender, System.EventArgs args)
	{
		string User_TnD = string.Format("{0:HH:mmtt dd-MMM-yyyy} {1}", DateTime.Now, s.UserID);
		string addfieldContents = string.Empty;

		addfieldContents = string.Format("{3}{0}{3}{1}{3}{2}{3}",
			"---------------------",
			User_TnD,
			txt_Follow_Add.Text,
			Environment.NewLine);

			edvUD103.dataView[edvUD103.Row]["Character04"] += addfieldContents;
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "In Progress";

	}



	private void epiBT_FOLLOW_Click(object sender, System.EventArgs args)
	{

		if (edvUD103.dataView[edvUD103.Row]["ShortChar10"] == "YES")
		{
			edvUD103.dataView[edvUD103.Row].BeginEdit();
			//1. UD103.ShortChar06 = "CLOSE"
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "CLOSE";
			//2. UD103.Date05  = NOW
			edvUD103.dataView[edvUD103.Row]["Date05"] = DateTime.Now;
			//3. UD103.ShortChar09 = Stamp time 2:00PM 1-APR-16 Cur-User
			edvUD103.dataView[edvUD103.Row]["ShortChar09"] = string.Format("{0:HH:mmtt dd-MMM-yy} {1}", DateTime.Now, s.UserID);
			edvUD103.dataView[edvUD103.Row].EndEdit();
		}
		else if (edvUD103.dataView[edvUD103.Row]["ShortChar10"] == "NO")
		{
			edvUD103.dataView[edvUD103.Row].BeginEdit();
			//1. UD103.ShortChar06 = "OPEN"
			edvUD103.dataView[edvUD103.Row]["ShortChar06"] = "OPEN";
			//2. UD103.Date04  Date add 30 days
			edvUD103.dataView[edvUD103.Row]["Date04"] = DateTime.Now.AddDays(30);
			//3. Increase counter +1
			int cc = 0;
			cc = Convert.ToInt32(edvUD103.dataView[edvUD103.Row]["Number03"]);
			edvUD103.dataView[edvUD103.Row]["Number03"] = cc +1;
			//4. UD103.ShortChar09 = Stamp time 2:00PM 1-APR-16 Cur-User
			edvUD103.dataView[edvUD103.Row]["ShortChar09"] = "";
			edvUD103.dataView[edvUD103.Row]["ShortChar10"] = "";

			edvUD103.dataView[edvUD103.Row]["Character04"] += 
				string.Format("{3}{0}{3}{1}{3}{2}{3}",
							"---------------------",
							string.Format("{0:HH:mmtt dd-MMM-yy} {1}", DateTime.Now, s.UserID),
							"CAR was not sucessfull.  Extending audit date 30 days from today",
							Environment.NewLine);


			edvUD103.dataView[edvUD103.Row].EndEdit();
		}
	}
}
