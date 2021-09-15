import 'package:desktopapp/color/Color.dart';
import 'package:flutter/material.dart';

class Menu extends StatefulWidget {
  @override
  _MenuState createState() => _MenuState();
}

class _MenuState extends State<Menu> {
  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: <Widget>[
        Container(
          margin: const EdgeInsets.only(left: 10.0, top: 30.0),
          child: IconButton(
            icon: Image.asset('assets/icon/logo.png'),
            iconSize: 75,
            splashColor: Colors.white,
            onPressed: () {},
          ),
        ),
        Container(
          width: 100,
          height: 10,
          child: Divider(
            indent: 18,
            endIndent: 0,
            color: dividercolor,
          ),
        ),
        Container(
          margin: const EdgeInsets.only(left: 10.0, top: 10.0),
          child: IconButton(
            icon: Image.asset('assets/icon/adddata.png'),
            iconSize: 75,
            splashColor: Colors.white,
            onPressed: () {},
          ),
        ),
      ],
    );
  }
}
