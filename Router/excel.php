$type = $_POST["type"];
require_once '../../lib/PHPExcel-1.8/Classes/PHPExcel.php';
$filename = $_FILES['file_excel']['name'];
$excel = $_FILES['file_excel']['tmp_name'];
$folder = '../../file/';
move_uploaded_file($excel, $folder . $filename);
$data = PHPExcel_IOFactory::load($folder . $filename);
$data->setActiveSheetIndex(0);
$i = 2;
$INSERT = "";
while ($data->getActiveSheet()->getCell('A' . $i)->getValue() != "") {
$name = $data->getActiveSheet()->getCell('A' . $i)->getValue();
$password = md5($data->getActiveSheet()->getCell('B' . $i)->getValue());
$email = $data->getActiveSheet()->getCell('C' . $i)->getValue();
$id_student = $data->getActiveSheet()->getCell('D' . $i)->getValue();
$TEL = $data->getActiveSheet()->getCell('E' . $i)->getValue();
$Address = $data->getActiveSheet()->getCell('F' . $i)->getValue();
$INSERT = "INSERT Into login (name, password, email, id_student, Type, TEL, Address)
values(
'" . $name . "'
, '" . $password . "'
, '" . $email . "'
, '" . $id_student . "'
, '" . $type . "'
, '" . $TEL . "'
, '" . $Address . "'
)";
$stmt = $conn->prepare($INSERT);
$stmt->execute();
$i++;
}
$stmt->close();
$conn->close();