# 数据的连接
## 代码文件中连接
```c++
	//创建mysql数据库对象
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	//本地localhost,远程填ip地址
    db.setHostName("bigblue");
    //指定连接的数据库的名称
    db.setDatabaseName("flightdb");
    //指定连接的数据库的账户和密码
    db.setUserName("acarlson");
    db.setPassword("1uTbSbAs");

	//开关
    bool ok = db.open();
    bool ok1 = db.close();
```
- ip地址 123.56.154.190
- 账户 travel-system-database
- 密码 Q2SWraFR3zKAP3bD
- 数据库名称 travel-system
## 配置文件连接
- 通过读取配置文件的信息来连接（.ini文件）
- 通过QSettings类来读取
```c++
//配置文件
[Database]  
host=localhost  
port=3306  
database=mydb  
user=root  
password=yourpassword


//读取代码
QSettings settings("config.ini", QSettings::IniFormat); QString host = settings.value("Database/host").toString(); QString port = settings.value("Database/port").toString(); QString database = settings.value("Database/database").toString(); 
QString user = settings.value("Database/user").toString(); QString password = settings.value("Database/password").toString();
```

# 数据的增删改查
## qt中提供的实现类
- 最底层
	- QSqlQuery 
- 高级封装
	- QSqlQueryModel（只读）
	- QSqlTableModel
	- QSqlRelationalTableModel

### QSqlQueryModel
- 只读
- 数据行以索引形式读取
```c++
	QSqlQueryModel model;
	//读取employee表的全部数据，employee改成需要的表名即可
    model.setQuery("SELECT * FROM employee");

	//索引读取
    for (int i = 0; i < model.rowCount(); ++i) {
	    //record(int index)方法获取对应行
	    //value("字段名")获取对应数据
        int id = model.record(i).value("id").toInt();
        QString name = model.record(i).value("name").toString();
        qDebug() << id << name;
    }
```
- 数据类型对照
	- 各种int             ->      int
	- text, varchar   ->     String
	- float                 ->     float
	- 后面最好像样例代码进行显式转换

## QSqlTableModel
- 可读写
- 读取类似QSqlQueryModel，不需要修改数据的时候没必要使用
```c++
	QSqlTableModel model;
	//需要进行sql语句的拆分设置
    model.setTable("employee");
    model.setFilter("salary > 50000");
    model.setSort(2, Qt::DescendingOrder);
    model.select();

	//读取类似QSqlQueryModel
    for (int i = 0; i < model.rowCount(); ++i) {
        QString name = model.record(i).value("name").toString();
        int salary = model.record(i).value("salary").toInt();
        qDebug() << name << salary;
    }


	//改
	//设置数据setRecord，setValue方法
	for (int i = 0; i < model.rowCount(); ++i) {
		//QSqlRecord记录行数据
        QSqlRecord record = model.record(i);
        double salary = record.value("salary").toInt();
        salary *= 1.1;
        //setValue指定类名和数据
        record.setValue("salary", salary);
        //setRecord设置行数据
        model.setRecord(i, record);
    }
    
	//使用setData方法修改数据
	model.setData(model.index(row, column), 75000);


	//增
	model.insertRows(row, 1);

	
	//删
	model.removeRows(row, 5)


	//将数据变化提交给数据库
    model.submitAll();
```
- submitAll() 的使用受编辑策略影响
	- `setEditStrategy()` 方法修改
	- `QSqlTableModel::OnRowChange`（默认），该策略指定在用户选择不同的行时，将挂起的更改应用到数据库中
	- `QSqlTableModel::OnManualSubmit`，所有更改会缓存在模型中，直到显式调用 `submitAll()` 方法
	- `QSqlTableModel::OnFieldChange`，不会缓存更改，每当字段变化时立即将更改提交到数据库。这种策略适用于希望每次更改字段后立刻更新数据库的需求。