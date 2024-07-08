//登录流程：
//1.用户输入用户名、密码，点击登录后调用Login(string name, string password)

//2.Login 调用check函数，首先查找表中用户名是否存在
    //若存在，调用isPasswordEqual(name，password)函数判断，密码是否正确（isequal内部获取数据库中的密码来判断）
        //若正确，返回登录的信号
            //执行enableUser(),用数据库中该用户的数据实例化一个user对象，并返回
        //若错误，返回密码错误的代号
    //若不存在，返回用户名不存在的信号


//注册流程：
//1.用户输入用户名，密码，点击后调用Register(string name, string password)

//2.在数据库中查询用户名是否存在isExist(string name)
    //若存在返回用户名存在的信号
    //若不存在，addUser(string name, string password)，同时在数据库中添加用户信息

//具体需要的接口如下：

//查找用户名为name的数据
//查找到的数据条数不为0则返回true，表示存在
//查找到的数据条数为0则返回false，表示不存在
bool isExist(string name);

//根据传入参数在数据库中添加新数据
//成功添加则返回true，否则返回false（避免用户名存在）
bool addUser(string name, string password);

//根据用户名查找对应的密码，判断密码是否正确
//正确则返回true，错误返回false
bool isPasswordEqual(string name, string password);

//根据用户名查找数据，并根据数据构建User，返回一个User
User enableUser(string name);


