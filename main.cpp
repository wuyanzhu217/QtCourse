#include "mainwidget.h"

#include <QApplication>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // // 1. 配置数据库连接（SQLite）
    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("test.db");
    // if (!db.open()) {
    //     qDebug() << "数据库打开失败：" << db.lastError().text();
    //     return 1;
    // }
    // // 2. 检查并创建 users 表（如果不存在）
    // QSqlQuery query;
    // QString createTableSql = R"(
    //     CREATE TABLE IF NOT EXISTS users (
    //         id INTEGER PRIMARY KEY AUTOINCREMENT,
    //         username TEXT NOT NULL,
    //         email TEXT
    //     )
    // )";
    // if (!query.exec(createTableSql)) {
    //     qDebug() << "创建表失败：" << query.lastError().text();
    //     return 1;
    // } query.exec("SELECT COUNT(*) FROM users");
    // if (query.next() && query.value(0).toInt() == 0) {
    //     query.exec("INSERT INTO users (username, email) VALUES ('Alice', 'alice@example.com')");
    //     query.exec("INSERT INTO users (username, email) VALUES ('Bob', 'bob@example.com')");
    //     query.exec("INSERT INTO users (username, email) VALUES ('Charlie', 'charlie@example.com')");
    // }
    // // 2. 创建并配置 QSqlQueryModel
    // QSqlQueryModel *model = new QSqlQueryModel;
    // model->setQuery("SELECT * FROM users"); // 执行 SQL 查询

    // // 检查查询是否成功
    // if (model->lastError().isValid()) {
    //     qDebug() << "查询失败：" << model->lastError().text();
    //     return 1;
    // }

    // // 可选：自定义列名
    // model->setHeaderData(0, Qt::Horizontal, "ID");
    // model->setHeaderData(1, Qt::Horizontal, "用户名");
    // model->setHeaderData(2, Qt::Horizontal, "邮箱");

    // // 3. 创建视图并绑定模型
    // QTableView *view = new QTableView;
    // view->setModel(model);
    // view->resize(600, 400);
    // view->show();
    Widget w;
    w.show();
    return a.exec();
}
