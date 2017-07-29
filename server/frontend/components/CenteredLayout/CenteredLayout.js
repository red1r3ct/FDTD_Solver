import React from 'react';
import styles from './CenteredLayout.css';

export const CenteredLayout = ({ children }) => (
	<div className={styles.container}>
		{children}
	</div>
);

export default CenteredLayout;
