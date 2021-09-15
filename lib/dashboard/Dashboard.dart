import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';
import 'MeneSave.dart';
import 'Menu.dart';
import 'Topic.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: bgcolor,
      body: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          // Menu
          Menu(),
          // Dashboard
          Card(
            shape:
                RoundedRectangleBorder(borderRadius: BorderRadius.circular(53)),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              mainAxisAlignment: MainAxisAlignment.start,
              children: [
                // หัวข้อ ไม่ใช่หัวเข่า
                Topic(),
                SizedBox(
                  height: 6,
                ),
                // เมนู ปลาซามอล
                MenuSave(),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
