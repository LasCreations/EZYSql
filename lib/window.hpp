#pragma once

#include "Sql.hpp"

#include <string>
#include <vector>
#include <iostream>

#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>

class Screen : public Gtk::Window{

	protected:
        	
		Gtk::Fixed *MainFixed =Gtk::manage(new Gtk::Fixed());
		Gtk::ScrolledWindow *MainScrolledWindow = Gtk::manage(new Gtk::ScrolledWindow());
		Gtk::Box *MainBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL)); 
        	
		Gtk::Entry *username = Gtk::manage(new Gtk::Entry());
        	Gtk::Entry *password = Gtk::manage(new Gtk::Entry());

        	Gtk::Button *LoginBtn = Gtk::manage(new Gtk::Button("Login")); 
        	Gtk::Button *ExitBtn = Gtk::manage(new Gtk::Button("Exit")); 

		Gtk::Paned *Paned = Gtk::manage(new Gtk::Paned(Gtk::ORIENTATION_HORIZONTAL)); 

		Gtk::Box *SidebarBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
		
        	Gtk::Entry *NewDatabaseEntry = new Gtk::Entry();
        	Gtk::MessageDialog *NewDatabaseDialog = new Gtk::MessageDialog("EZYSql", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_NONE, true);
		
        	Gtk::Entry *QueryEntry = Gtk::manage(new Gtk::Entry());
		
        	Gtk::MenuBar *menuBar = Gtk::manage(new Gtk::MenuBar());

        	Gtk::MenuItem *menuFile = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuEdit = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuView = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuQuery = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuTools = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuHelp = Gtk::manage(new Gtk::MenuItem());
        
        	Gtk::Menu *subMenuFile = Gtk::manage(new Gtk::Menu());
        	Gtk::Menu *subMenuEdit = Gtk::manage(new Gtk::Menu());
        	Gtk::Menu *subMenuView = Gtk::manage(new Gtk::Menu());
        	Gtk::Menu *subMenuHelp = Gtk::manage(new Gtk::Menu());
        
        	Gtk::MenuItem *menuFileNew = Gtk::manage(new Gtk::MenuItem());
        	Gtk::SeparatorMenuItem *separator1 = Gtk::manage(new Gtk::SeparatorMenuItem());
        	Gtk::MenuItem *menuFileOpen = Gtk::manage(new Gtk::MenuItem());
        	Gtk::MenuItem *menuFileClose = Gtk::manage(new Gtk::MenuItem());

        	class ModelColumns : public Gtk::TreeModel::ColumnRecord{
            		public:
                		
				ModelColumns(){
		    			add(ManageColumn); 
                		}
            			
				Gtk::TreeModelColumn<Glib::ustring> ManageColumn;
        	};

		Gtk::Box *SideBarBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
  		Gtk::ScrolledWindow *SideBarScrolledWindow = Gtk::manage(new Gtk::ScrolledWindow());

        	ModelColumns SideBarColumns;

        	Gtk::TreeView *SideBarTreeView = Gtk::manage(new Gtk::TreeView());
       	 	Glib::RefPtr<Gtk::TreeStore> SideBarRefPtrTreeModel;
		
        	Gtk::Notebook *MainNotebook = Gtk::manage(new Gtk::Notebook());
        	Gtk::Label m_Label1;
                
		//Signal Handlers 
		void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        	void on_notebook_switch_page(Gtk::Widget* page, guint page_num);
        	void on_login_clicked();
        	void on_exit_clicked();
        	void on_New_Database_clicked();	
	
		vector <string> DBNames;

    	private:
        	Sql sql; 

    	public:
        	Screen();
        	virtual ~Screen();

        	void SetDbName();
        	void Login();
        	void ErrDialogLogin();
        	void Main();
};
