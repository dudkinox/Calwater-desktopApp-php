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
    // return Menu();
    return Scaffold(
      backgroundColor: background,
      body: Menu();

    );
  }
}
