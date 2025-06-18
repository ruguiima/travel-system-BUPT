# 📦 数据库导入与配置说明

本项目使用 **MySQL** 作为后端数据库。若远程数据库失效，您可以通过以下步骤快速在本地部署数据库以正常运行程序。

## 1️⃣ 数据库导入说明

本目录下包含导出的数据库结构与数据文件：`dump.sql`。

### ✅ 导入步骤：

1. 确保本地已安装 MySQL 数据库（推荐版本：8.0+）。
2. 创建数据库（若尚未存在）：

   ```bash
   mysql -u your_username -p -e "CREATE DATABASE your_database_name DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;"
   ```
3. 将数据导入至新创建的数据库：
   
   ```bash
   mysql -u your_username -p your_database_name < dump.sql
   ```
## 2️⃣ 数据库连接配置

  请确保运行目录下包含`config.ini`。打开该文件，修改为您的数据库参数。

  ```text
   [Database]
   hostname = your_host_name
   dbname = your_database_name
   username = your_username
   password = your_password
   ```

