
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package project;
import java.sql.*;
import static java.lang.Class.forName;

/**
 *
 * @author hydee2012
 */
public class connectionprovider {
    public static Connection getCon()
    {
    try
    {
        Class.forName("com.mysql.jdbc.Driver");
        Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/project", "root", "123456");
        return con;
    }
    catch(Exception e)
    {
    return null;
    }
    }
}
