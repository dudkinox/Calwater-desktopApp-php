import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

import 'Menu.dart';

class Dashboard extends StatefulWidget {
  @override
  _DashboardState createState() => _DashboardState();
}

class _DashboardState extends State<Dashboard> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: background,
      body: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          // Menu
          Menu(),
          // Dashboard
          Column(
            children: [
              Card(
                child: Padding(
                  padding: EdgeInsets.symmetric(
                    vertical: 100,
                    horizontal: 300,
                  ),
                  child: Container(
                    child: Column(
                      children: [
                        Column(
                          children: [
                            ListView.builder(
                              itemCount: 3,
                              itemBuilder: (context, index) {
                                return Card(
                                  child: Text("test"),
                                );
                              },
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            ],
          ),
        ],
      ),
    );
  }
}
