import tarfile


def read(path):
    """
    Читает архив и возвращает список всех файлов
    @param path - путь до архива
    """
    tar = tarfile.open(path)
    return list(tar.getmembers()), tar


def read_file_as_array(tar_file, file_tar_info):
    """
    Читает определенный файл из архива в виде numpy массива
    @param tar_file - TarFile из которого читаем
    @param file_tar_info - tar_info файла
    """
    f = tar_file.extractfile(file_tar_info)
    if f is None:
        return None, True
    content = f.read()
    return content, False
