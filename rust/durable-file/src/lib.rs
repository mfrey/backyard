use std::fs::File;
use std::io::{Result,Write};

struct DurableFile {
    file: File,
    needs_sync: bool,
}

impl DurableFile {
    pub fn new(file: std::fs::File) -> DurableFile {
        DurableFile {
            file,
            needs_sync: false
        }
    }
}

impl From<File> for DurableFile {
    fn from(file: File) -> Self {
        DurableFile {
            file,
            needs_sync: false
        }
    }
}

impl Write for DurableFile {
    fn write(&mut self, buf: &[u8]) -> Result<usize> {
        let bytes_written = self.file.write(buf)?;
        self.needs_sync = true;
        Ok(bytes_written)
    }

    fn flush(&mut self) -> Result<()> {
        self.file.sync_all()?;
        self.needs_sync = false;
        Ok(())
    }
}
