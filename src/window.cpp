#include "../lib/window.hpp"

Screen::Screen(): m_Label1("Welcome to EZYSql\n Select a Database\n\n\n\n\n"){ 
	set_title("EZYSql"); 
    	set_position(Gtk::WIN_POS_CENTER); 
    	set_border_width(10); 
    	Login();
}

void Screen::Login(){
	resize(300, 300);
    
    	add(*MainBox);
    	MainBox->add(*MainFixed);
     
    	username->set_placeholder_text("Username"); 
    	password->set_placeholder_text("Password"); 
   
	password->set_visibility(false);       

    	MainFixed->add(*username);
    	MainFixed->add(*password);
    
   	MainFixed->move(*username, 50, 10);
    	MainFixed->move(*password, 50, 60);
    
    	ExitBtn->set_size_request(15, 25);
    	LoginBtn->set_size_request(15, 25);
    
    	MainFixed->add(*ExitBtn);
    	MainFixed->add(*LoginBtn);
    
    	MainFixed->move(*ExitBtn, 150, 130);
    	MainFixed->move(*LoginBtn, 40, 130);
    
    	ExitBtn->signal_clicked().connect(sigc::mem_fun(*this,&Screen::on_exit_clicked));
    	LoginBtn->signal_clicked().connect(sigc::mem_fun(*this,&Screen::on_login_clicked));
    
    	show_all();
}

void Screen::Main(){
	
	maximize();

	MainFixed = new Gtk::Fixed();

	MainBox->pack_start(*menuBar, Gtk::PACK_SHRINK);

    	MainBox->pack_end(*MainScrolledWindow);

    	MainScrolledWindow->add(*MainFixed);

    	menuFile->set_label("File");
    	menuView->set_label("View");
    	menuQuery->set_label("Query");
    	menuTools->set_label("Tools");
    	menuHelp->set_label("Help");
    
    	menuBar->append(*menuFile);
    	menuBar->append(*menuView);
    	menuBar->append(*menuQuery);
    	menuBar->append(*menuTools);
    	menuBar->append(*menuHelp);

    	menuFile->set_submenu(*subMenuFile);

    	subMenuFile->append(*menuFileNew);
    	subMenuFile->append(*menuFileOpen);
    	subMenuFile->append(*separator1);
    	subMenuFile->append(*menuFileClose);

    	menuFileNew->set_label("_New");
    	menuFileOpen->set_label("_Open");
    	menuFileClose->set_label("_Close");
    
    	menuFileNew->set_use_underline(true);
    	menuFileOpen->set_use_underline(true);
    	menuFileClose->set_use_underline(true);
    
    	menuFileNew->signal_activate().connect(sigc::mem_fun(*this,&Screen::on_New_Database_clicked));
    	menuFileClose->signal_activate().connect([&](){ hide(); });

    	menuFileOpen->signal_activate().connect([&](){ std::cout << "MainMenu/File/Open" << std::endl; }); 
	
	SideBarRefPtrTreeModel = Gtk::TreeStore::create(SideBarColumns);

    	SideBarTreeView->set_model(SideBarRefPtrTreeModel);

    	SideBarTreeView->set_reorderable();

    	DBNames = sql.DatabaseAvailable();

    	for(size_t i =0 ; i< DBNames.size(); i++){
    		Gtk::TreeModel::Row row = *(SideBarRefPtrTreeModel->append());
    		row[SideBarColumns.ManageColumn] = DBNames[i];
    	}
  
    	SideBarTreeView->append_column("Manage", SideBarColumns.ManageColumn);

    	SideBarTreeView->signal_row_activated().connect(sigc::mem_fun(*this,&Screen::on_treeview_row_activated));

	Paned = new Gtk::Paned(Gtk::ORIENTATION_HORIZONTAL);

    	MainBox->add(*Paned);
	
	Paned->add1(*SideBarTreeView);
	Paned->add2(*MainNotebook); 

	
	MainNotebook->append_page(*QueryEntry, "New");
	MainNotebook->append_page(m_Label1, "Welcome");
	
	//QueryEntry->set_size_request(100, 100);
    	//QueryEntry->set_margin_top(0);	
	
	MainNotebook->signal_switch_page().connect(sigc::mem_fun(*this,&Screen::on_notebook_switch_page));
   		
	show_all();

}

void Screen::on_exit_clicked(){
	hide();
}

void Screen::on_login_clicked(){

    	if(sql.Login(username->get_text(), password->get_text())){
		delete ExitBtn;
        	delete LoginBtn;
        	delete username;
        	delete password;
        	delete MainFixed;
        	Main();
    	}else{
		ErrDialogLogin();
    	}
}

void Screen::on_New_Database_clicked(){
	NewDatabaseEntry = new Gtk::Entry();
    
    	NewDatabaseDialog = new Gtk::MessageDialog("EZYSql", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_NONE, true);
    
    	NewDatabaseDialog->get_vbox()->pack_start(*NewDatabaseEntry, Gtk::PACK_SHRINK);
    
    	NewDatabaseDialog->set_title("Create A Database");
    
    	NewDatabaseDialog->set_secondary_text("Enter Database Name");
    
    	NewDatabaseDialog->add_button("Create", Gtk::BUTTONS_OK);
    
    	NewDatabaseDialog->signal_response().connect([&](int response_id){ SetDbName(); });

    	NewDatabaseDialog->set_size_request(200,100);

    	NewDatabaseDialog->show_all();
}

void Screen::on_treeview_row_activated(const Gtk::TreeModel::Path& path,Gtk::TreeViewColumn* /* column */){
    	Gtk::TreeModel::iterator iter = SideBarRefPtrTreeModel->get_iter(path);
   	//Gtk::TreeModel::iterator store_iter = SideBarRefPtrTreeModel->get_iter(path);    	
	
    	if(iter){
        	Gtk::TreeModel::Row row = *iter;
        	//std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name="<< row[m_Columns.m_col_name] << std::endl;
        	std::cout << " Name=" << row[SideBarColumns.ManageColumn] << std::endl;	
    	}
	
	//SideBarRefPtrTreeModel->erase(store_iter); 
}

void Screen::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num){
  	//std::cout << "Switched to tab with index " << page_num << std::endl;
  	//You can also use m_Notebook.get_current_page() to get this index.
}

void Screen::SetDbName(){
    	
	if(!(NewDatabaseEntry->get_text().empty())){
        	sql.CreateDatabase(NewDatabaseEntry->get_text());
    		Gtk::TreeModel::Row row = *(SideBarRefPtrTreeModel->append());
		row[SideBarColumns.ManageColumn] = NewDatabaseEntry->get_text();
    	}

    	delete NewDatabaseEntry; 
    	delete NewDatabaseDialog;
}

void Screen::ErrDialogLogin(){  
    	Gtk::MessageDialog dlg("EZYSql", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    
    	dlg.set_title("Login Failed");
    
    	dlg.set_secondary_text("Please Ensure That MySql Is Enabled In System\n\nIncorrect Password/Username");
    
    	dlg.run();

}

Screen::~Screen(){}

