#include "../lib/Sql.hpp"

bool Sql::Login(std::string username, std::string password){
	try{
        	if((this->driver = get_driver_instance())){
		
		}
        	if((this->con = driver->connect("localhost", username, password))){
            		this->stmt = con->createStatement();
        	}
    	}catch(sql::SQLException &e){
        	return false;
    	}
    	
	return true;
}

vector<string> Sql::DatabaseAvailable(){
	vector <string> DBNames;
	res = stmt->executeQuery("SHOW DATABASES;"); 
	while(res->next()){
		DBNames.push_back(res->getString("Database"));
    	}
	return DBNames;

}

void Sql::CreateDatabase(std::string dbName){
	std::string dropDB = "DROP DATABASE IF EXISTS " + dbName;
    	std::string createDB = "CREATE DATABASE IF NOT EXISTS " + dbName;
    	std::string useDB = "USE " + dbName;

    	stmt->execute(dropDB);
    	stmt->execute(createDB);
    	stmt->execute(useDB);
}

void Sql::CreateTable(){
    	stmt->execute("DROP TABLE IF EXISTS inventory");
    	stmt->execute("CREATE TABLE inventory(id INTEGER PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
}

void Sql::Insert(){
    	prep_stmt = con->prepareStatement("INSERT INTO inventory(id, name, quantity) VALUES(?,?,?)");
    
    	prep_stmt->setInt(1,74764894);
    	prep_stmt->setString(2, "Snacks");
    	prep_stmt->setInt(3, 123);
    	prep_stmt->execute();

    	prep_stmt->setInt(1,453464);
    	prep_stmt->setString(2, "Sodas");
    	prep_stmt->setInt(3, 85);
    	prep_stmt->execute();

    	prep_stmt->setInt(1,485984);
    	prep_stmt->setString(2, "Alcohol");
    	prep_stmt->setInt(3, 10);
    	prep_stmt->execute();
}


void Sql::Read(){
    	res = stmt->executeQuery("SELECT id,name,quantity FROM inventory");
    	cout<<"\nDisplaying data from Database"<<endl;

    	while(res->next()){
    		cout << "ID: " << res->getInt(1) <<endl;
    		cout << "Item Name: " << res->getString("name") <<  endl;
    		cout << "Quantity : " << res->getInt(3) <<endl;
    		cout << "\n" <<endl;
    	}
}
