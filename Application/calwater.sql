-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 07, 2021 at 01:34 PM
-- Server version: 10.4.19-MariaDB
-- PHP Version: 8.0.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `calwater`
--

-- --------------------------------------------------------

--
-- Table structure for table `ca`
--

CREATE TABLE `ca` (
  `model` decimal(50,2) NOT NULL,
  `lab` decimal(50,2) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

-- --------------------------------------------------------

--
-- Table structure for table `fe`
--

CREATE TABLE `fe` (
  `model` decimal(50,2) NOT NULL,
  `lab` decimal(50,2) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

-- --------------------------------------------------------

--
-- Table structure for table `info`
--

CREATE TABLE `info` (
  `ID` int(100) NOT NULL,
  `Volume` decimal(50,9) NOT NULL,
  `Batch_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Meet_MOI_Spec` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Sump_No` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Treatment_Date` varchar(100) COLLATE utf8mb4_unicode_nopad_ci NOT NULL,
  `Ca` int(10) NOT NULL,
  `Fe` int(10) NOT NULL,
  `Na` int(10) NOT NULL,
  `TDS` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Dumping data for table `info`
--

INSERT INTO `info` (`ID`, `Volume`, `Batch_No`, `Meet_MOI_Spec`, `Sump_No`, `Treatment_Date`, `Ca`, `Fe`, `Na`, `TDS`) VALUES
(1, '10.000000000', 'S2202101', 'YES', 'S2', '10/07/2021', 1, 1, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `na`
--

CREATE TABLE `na` (
  `model` decimal(50,2) NOT NULL,
  `lab` decimal(50,2) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

-- --------------------------------------------------------

--
-- Table structure for table `tds`
--

CREATE TABLE `tds` (
  `model` decimal(50,2) NOT NULL,
  `lab` decimal(50,2) NOT NULL,
  `No` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_nopad_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ca`
--
ALTER TABLE `ca`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `fe`
--
ALTER TABLE `fe`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `info`
--
ALTER TABLE `info`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `na`
--
ALTER TABLE `na`
  ADD PRIMARY KEY (`No`);

--
-- Indexes for table `tds`
--
ALTER TABLE `tds`
  ADD PRIMARY KEY (`No`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `info`
--
ALTER TABLE `info`
  MODIFY `ID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
